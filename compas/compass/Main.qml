import QtQuick
import QtQuick.Window
import QtQuick.Controls

import Compass

Window {
    width: 640
    height: 480
    visible: true

    function onLineNumberReady (theLineNumber){
        myOutput.text = theLineNumber;
    }

    Column {
        anchors.fill: parent

        Compass { id: myCompass }

        TextField {
            id: myInput
            anchors.left: parent.left
            anchors.right: parent.right
            placeholderText: "num_1,num_2,num_3,num_4"
            font.pixelSize: 16
        }
        Button {
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Calculate"
            onClicked: myCompass.calculateAverageSlot (myInput.text)
        }
        Text {
            id: myOutput
            anchors.left: parent.left
            anchors.right: parent.right
            color: grey
            font.pointSize: 24
            horizontalAlignment: myOutput.AlignHCenter
        }
    }

    Component.onCompleted: {
        myCompass.lineSumberReadySignal.connect (onLineNumberReady)
    }
}
