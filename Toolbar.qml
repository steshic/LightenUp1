import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    signal newGame()
    signal quitApp()

    property int countdown: 600

    Button{
        id: newGameButton

        text: "New Game"
        onClicked: {
            countdown = 600
            newGame()
        }
    }

    TextField {
        id:timerField
        enabled:false
        font.pointSize: 20
        color: "red"
        Layout.fillWidth: true
    }

    Timer {
        interval: 1000
        running : (countdown > 0)
        repeat  : true


        onTriggered: {
           timerField.text = Math.floor(countdown/60) + ":" + Math.floor(countdown%60)
             countdown--

       //   timerField.text =  ((countdown / 60 >= 1) ? ((countdown/ 60 == 2) ? 2 : 1) : 0).toString() + ":" + (((countdown <= 69) && (countdown >= 60)) ? "0" : '') + (((countdown <= 9) && (countdown >= 0)) ? "0" : '')+ (countdown % 60).toString() + (countdown == 120 ? "0" : '')
            if ((gameplay.check()) && (countdown != 0)){
                dialogWin.visible = true
                dialogWin.open()
                countdown = 0
            }
            else if (countdown ==0){
                timerField.text = "00:00"
                dialogLose.visible = true
                dialogLose.open()
            }

        }
    }

    Button{
        id:quitButton
        text: "Quit"
        onClicked: quitApp()
    }

    Shortcut{
        context: Qt.ApplicationShortcut
        sequences: ["Ctrl+N"]
        onActivated: newGame()
    }

    Shortcut{
        context: Qt.ApplicationShortcut
        sequences: [StandardKey.Close ,"Ctrl+Q"]
        onActivated: quitApp()
    }


}
