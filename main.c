#include <gst/gst.h>

int main(int argc, char *argv[]) {
    GstElement *pipeline, *v4l2src, *videoconvert, *x264enc, *rtspclientsink;
    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Create the elements */
    pipeline = gst_pipeline_new("pipeline");
    v4l2src = gst_element_factory_make("v4l2src", "v4l2src");
    videoconvert = gst_element_factory_make("videoconvert", "videoconvert");
    x264enc = gst_element_factory_make("x264enc", "x264enc");
    rtspclientsink = gst_element_factory_make("rtspclientsink", "rtspclientsink");

    /* Create the pipeline */
    if (!pipeline || !v4l2src || !videoconvert || !x264enc || !rtspclientsink) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    /* Build the pipeline */
    gst_bin_add_many(GST_BIN(pipeline), v4l2src, videoconvert, x264enc, rtspclientsink, NULL);
    if (!gst_element_link_many(v4l2src, videoconvert, x264enc, rtspclientsink, NULL)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    /* Set the device ID for the camera */
    g_object_set(v4l2src, "device", "/dev/video0", NULL);

    /* Set the RTSP location */
    g_object_set(rtspclientsink, "location", "rtsp://localhost:8554/mystream", NULL);

    /* Start playing */
    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set the pipeline to the playing state.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* Free resources */
    if (msg != NULL)
        gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}

// gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:8554/mystream latency=0 ! decodebin ! autovideosink