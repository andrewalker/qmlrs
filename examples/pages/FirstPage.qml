import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        contentHeight: column.height
        anchors.fill: parent

        VerticalScrollDecorator {}

        Column {
            spacing: Theme.paddingLarge
            id: column
            width: parent.width

            PageHeader {
                title: "Silica components"
                id: header
            }

            Label {
                id: factorialResult
                anchors {
                       left: parent.left
                       right: parent.right
                       margins: Theme.paddingLarge
                }
            }

            Button {
                text: "Ask me"
                onClicked: {
                    var dialog = pageStack.push(Qt.resolvedUrl("Dialog.qml"))
                    dialog.accepted.connect(function() {
                        factorialResult.text = "Result is: " + factorial.calculate(dialog.mynumber)
                    })
                }
            }
        }
    }
}
