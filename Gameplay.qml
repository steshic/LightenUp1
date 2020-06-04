import QtQuick 2.12
import QtQuick.Layouts 1.12

GridLayout {
    id:gl

    width: 600
    height: 600

    columns: 10
    rows: 10

    columnSpacing: 0
    rowSpacing: 0


    function newGame(){

        var newGameConfigs = helper.newGame()
        for (var i = 0; i < newGameConfigs.length; i++)
            bricks.itemAt(i).config = newGameConfigs[i]
        light()

    }

    function light() {
        var brickConfigs = []

        for (var i = 0; i < bricks.count; i++) {
            brickConfigs.push(bricks.itemAt(i).config)
        }
        var brickLights = helper.light(brickConfigs)
        for (var j = 0; j < brickLights.length; j++)
            bricks.itemAt(j).light = brickLights[j]
    }

    function check() {
        var number= 0
        var winned = false
        for (var i = 0; i < bricks.count; i++) {
            if (bricks.itemAt(i).light)
                number++
        }

        console.log(number)
        if (number === 100)
            winned = true
        return winned
    }

    Repeater{
        id:bricks
        model:100

        Brick {
            onRotated: gl.light()
        }

    }

    Component.onCompleted: {
        newGame()
    }
}
