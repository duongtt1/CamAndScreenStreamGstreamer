import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.9

ApplicationWindow {
    width: 1024
    height: 600
    color: "#ffffff"
    visible: true

    property string urlClient1: "rtsp://localhost:8554/client1"

    Item {
        anchors.centerIn: parent.center
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: 512
        height: 300
        Row {
            width: parent.width + 50
            height: parent.height
            spacing: 50
            anchors.horizontalCenter: parent.horizontalCenter
            RtspPlayer {
                width:  parent.width
                height: parent.height
                url: urlClient1
            }
        }
    }
}
