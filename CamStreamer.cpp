#include <gst/gst.h>
#include <iostream>
#include <string>

class CamStreamer {
private:
    GstElement *pipeline, *v4l2src, *videoscale;
    GstElement *videoconvert;
    GstElement *x264enc, *h264parse, *rtspclientsink;
    GstBus *bus;
    GstMessage *msg;

public:

    bool createElements()
    {
        // Create elements
        pipeline        = gst_pipeline_new("pipeline");
        v4l2src       = gst_element_factory_make("v4l2src", "v4l2src-source");
        videoconvert   = gst_element_factory_make("videoconvert", "video-convert");
        x264enc         = gst_element_factory_make("x264enc", "x264-encoder");
        h264parse       = gst_element_factory_make("h264parse", "h264-parser");
        rtspclientsink  = gst_element_factory_make("rtspclientsink", "rtsp-client-sink");

        // Check for element creation errors
        if (!pipeline || !v4l2src || !x264enc || !h264parse || !rtspclientsink) {
            g_printerr("One or more elements could not be created. Exiting.\n");
            return false;
        }

        return true;
    }

    bool buildPipeline(std::string url)
    {
        // Build the pipeline
        gst_bin_add_many(GST_BIN(pipeline), v4l2src, videoconvert, x264enc, h264parse, rtspclientsink, NULL);
        if (!gst_element_link_many(v4l2src, videoconvert, x264enc, h264parse, rtspclientsink, NULL)) {
            g_printerr("Elements could not be linked. Exiting.\n");
            return false;
        }

        // Set default properties
        g_object_set(v4l2src, "device", "/dev/video0", NULL);
        g_object_set(x264enc, "bitrate", 600, NULL);
        g_object_set(x264enc, "speed-preset", 1, NULL);
        g_object_set(x264enc, "tune", 0x00000004, NULL);

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

    CamStreamer() {
        // Initialize GStreamer
        gst_init(NULL, NULL);

        pipeline        = nullptr;
        v4l2src         = nullptr;
        x264enc         = nullptr;
        h264parse       = nullptr;
        rtspclientsink  = nullptr;
    }
    
    ~CamStreamer() {

    }
};

int main(int argc, char *argv[]) {
    CamStreamer streamer;
    streamer.createElements();
    std::string url = "rtsp://localhost:8554/client1cam";
    streamer.buildPipeline(url);
    streamer.startStreaming();
    return 0;
}
