#include <gst/gst.h>
#include <iostream>
#include <string>

class ScreenStreamer {
private:
    GstElement *pipeline, *ximagesrc, *videoscale;
    GstElement *videoconvert1, *capsfilter, *videoconvert2;
    GstElement *x264enc, *h264parse, *rtspclientsink;
    GstBus *bus;
    GstMessage *msg;
    GstCaps *caps;

public:

    bool createElements()
    {
        // Create elements
        pipeline = gst_pipeline_new("pipeline");
        ximagesrc = gst_element_factory_make("ximagesrc", "ximagesrc-source");
        videoscale = gst_element_factory_make("videoscale", "video-scale");
        videoconvert1 = gst_element_factory_make("videoconvert", "video-convert1");
        capsfilter = gst_element_factory_make("capsfilter", "caps-filter");
        videoconvert2 = gst_element_factory_make("videoconvert", "video-convert2");
        x264enc = gst_element_factory_make("x264enc", "x264-encoder");
        h264parse = gst_element_factory_make("h264parse", "h264-parser");
        rtspclientsink = gst_element_factory_make("rtspclientsink", "rtsp-client-sink");

        // Check for element creation errors
        if (!pipeline || !ximagesrc || !videoscale || !videoconvert1 || !capsfilter || !videoconvert2 || !x264enc || !h264parse || !rtspclientsink) {
            g_printerr("One or more elements could not be created. Exiting.\n");
            return false;
        }

        return true;
    }

    bool buildPipeline(std::string url)
    {
        // Build the pipeline
        gst_bin_add_many(GST_BIN(pipeline), ximagesrc, videoscale, videoconvert1, capsfilter, videoconvert2, x264enc, h264parse, rtspclientsink, NULL);
        if (!gst_element_link_many(ximagesrc, videoscale, videoconvert1, capsfilter, videoconvert2, x264enc, h264parse, rtspclientsink, NULL)) {
            g_printerr("Elements could not be linked. Exiting.\n");
            return false;
        }

        // Set default properties
        g_object_set(ximagesrc, "use-damage", 0, NULL);
        g_object_set(x264enc, "bitrate", 600, NULL);
        g_object_set(x264enc, "speed-preset", 1, NULL);
        g_object_set(x264enc, "tune", 0x00000004, NULL);

        caps = gst_caps_new_simple("video/x-raw",
                                    "width", G_TYPE_INT, 1024,
                                    "height", G_TYPE_INT, 680,
                                    "framerate", GST_TYPE_FRACTION, 30, 1,
                                    NULL);
        g_object_set(capsfilter, "caps", caps, NULL);
        gst_caps_unref(caps);

        // Set the RTSP location property
        g_object_set(rtspclientsink, "location", url.c_str(), NULL);

        return true;
    }

    void startStreaming()
    {
        // Set the pipeline to the playing stamain_screente
        GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
        if (ret == GST_STATE_CHANGE_FAILURE) {
            g_printerr("Unable to set the pipeline to the playing state. Exiting.\n");
            return;
        }

        // Wait until error or EOS
        bus = gst_element_get_bus(pipeline);
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

        // Parse message
        if (msg != NULL) {
            GError *err;
            gchar *debug_info;

            switch (GST_MESSAGE_TYPE(msg)) {
                case GST_MESSAGE_ERROR:
                    gst_message_parse_error(msg, &err, &debug_info);
                    g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
                    g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
                    g_clear_error(&err);
                    g_free(debug_info);
                    break;
                case GST_MESSAGE_EOS:
                    g_print("End of stream reached.\n");
                    break;
                default:
                    // Should not be reached
                    g_printerr("Unexpected message received.\n");
                    break;
            }
            gst_message_unref(msg);
        }

        // Free resources
        gst_object_unref(bus);
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    }

    ScreenStreamer() {
        // Initialize GStreamer
        gst_init(NULL, NULL);

        pipeline        = nullptr;
        ximagesrc       = nullptr;
        videoconvert1   = nullptr;
        capsfilter      = nullptr;
        videoconvert2   = nullptr;
        x264enc         = nullptr;
        h264parse       = nullptr;
        rtspclientsink  = nullptr;
    }

    ~ScreenStreamer() {
        // Clean up
        if (caps != NULL)
            gst_caps_unref(caps);
    }
};

int main(int argc, char *argv[]) {
    ScreenStreamer streamer;
    streamer.createElements();
    std::string url = "rtsp://localhost:8554/client1screen";
    streamer.buildPipeline(url);
    streamer.startStreaming();
    return 0;
}
