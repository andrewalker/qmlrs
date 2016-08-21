import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property int mynumber

    Column {
        width: parent.width

        DialogHeader { }
        TextField {
            width: 480
            id: numberField
            inputMethodHints: Qt.ImhDigitsOnly
            
            placeholderText: "Enter number"
            focus: true
            
        }
    }

    onDone: {
        if (result == DialogResult.Accepted) {
            mynumber = parseInt(numberField.text);
        }
    }
}
