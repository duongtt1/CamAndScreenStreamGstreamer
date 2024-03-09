import QtQuick 2.0
import QtQuick.Controls 2.2
import QtMultimedia 5.9

Item {
    property string url;
    property bool isCam: true

    Rectangle {
        id: mediaPlay
        color: "red"
        radius: 1
        border.width: 0
        anchors.fill: parent

        Video {
           id: frame
           width: mediaPlay.width
           height: mediaPlay.height
           source: url + (isCam === true ? "cam" : "screen")
           autoPlay: false
           opacity: 1.0
           fillMode: Image.Stretch
           muted: false
           onStatusChanged: {
               if (status === MediaPlayer.EndOfMedia) {
                   console.log("Video playback finished.")
                   pause()
               } else if (status === MediaPlayer.Loaded) {
                   console.log("Video loaded successfully.")
                   play()
               } else if (status === MediaPlayer.Error) {
                   console.error("Error loading or playing video.")
                   pause()
                }
       }
       }
    }
    Button {
        id: btnScreen
        anchors.top: mediaPlay.bottom
        anchors.left: mediaPlay.left
        anchors.topMargin: 10;
        width: mediaPlay.width/2 - 25
        height: mediaPlay.height/3
        text: "Screen"
        onClicked: {
            isCam = false;
            console.log(frame.source)
        }
    }
    Button {
        id: btnCam
        anchors.top: mediaPlay.bottom
        anchors.right: mediaPlay.right
        anchors.topMargin: 10;
        width: mediaPlay.width/2 - 25
        height: mediaPlay.height/3
        text: "Camera"
        onClicked: {
            isCam = true
            console.log(frame.source)
        }
    }
}
