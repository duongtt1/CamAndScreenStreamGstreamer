#include <gst/gst.h>

int main(int argc, char *argv[]) {
    GstElement *pipeline, *ximagesrc, *videoconvert, *queue, *x264enc, *rtspclientsink;
    GstBus *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Create elements */
    pipeline = gst_pipeline_new("mypipeline");
    ximagesrc = gst_element_factory_make("ximagesrc", "ximagesrc");
    videoconvert = gst_element_factory_make("videoconvert", "videoconvert");
    queue = gst_element_factory_make("queue", "queue");
    x264enc = gst_element_factory_make("x264enc", "x264enc");
    rtspclientsink = gst_element_factory_make("rtspclientsink", "rtspclientsink");

    /* Create the pipeline */
    if (!pipeline || !ximagesrc || !videoconvert || !queue || !x264enc || !rtspclientsink) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    /* Set properties */
    g_object_set(G_OBJECT(ximagesrc), "startx", 0, "starty", 0, "endx", 1920, "endy", 1080, "use-damage", FALSE, NULL);
    g_object_set(G_OBJECT(x264enc), "tune", 0, "bitrate", 2000000, "speed-preset", 1, NULL);
    g_object_set(G_OBJECT(rtspclientsink), "location", "rtsp://localhost:8554/mystream", NULL);

    /* Build the pipeline */
    gst_bin_add_many(GST_BIN(pipeline), ximagesrc, videoconvert, queue, x264enc, rtspclientsink, NULL);
    if (gst_element_link_many(ximagesrc, videoconvert, queue, x264enc, rtspclientsink, NULL) != TRUE) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

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
