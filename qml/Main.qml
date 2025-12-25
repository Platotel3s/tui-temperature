import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    width: 420
    height: 300
    visible: true
    title: qsTr("Suhu Converter — Modern (QML)")

    Rectangle {
        anchors.fill: parent
        color: "#1e1f29"

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 12
            width: parent.width * 0. Nine

            Text {
                text: "Konversi Suhu (Mode Dropdown)"
                font.pixelSize: 20
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ComboBox {
                id: combo
                Layout.fillWidth: true
                model: [
                    "Celsius → Fahrenheit",
                    "Celsius → Kelvin",
                    "Celsius → Reamur",
                    "Fahrenheit → Celsius",
                    "Fahrenheit → Kelvin",
                    "Fahrenheit → Reamur",
                    "Kelvin → Celsius",
                    "Kelvin → Fahrenheit",
                    "Kelvin → Reamur",
                    "Reamur → Celsius",
                    "Reamur → Fahrenheit",
                    "Reamur → Kelvin"
                ]
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 8

                TextField {
                    id: inputField
                    placeholderText: "Masukkan nilai suhu ..."
                    Layout.fillWidth: true
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    font.pixelSize: 16
                }

                Button {
                    text: "Konversi"
                    onClicked: {
                        // ambil nilai sebagai number; validasi
                        var val = parseFloat(inputField.text)
                        if (isNaN(val)) {
                            resultLabel.text = "Masukkan angka valid!"
                            return
                        }
                        // panggil C++ converter: index = combo.currentIndex
                        var out = converter.convert(combo.currentIndex, val)
                        resultLabel.text = "Hasil: " + out
                    }
                }
            }

            Label {
                id: resultLabel
                text: "Hasil: -"
                color: "#dbe9ff"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }

            // Footer kecil
            Text {
                text: "Tekan Esc untuk keluar"
                color: "#9aa6b2"
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    // keluar dengan Esc
    Keys.onReleased: {
        if (event.key === Qt.Key_Escape) Qt.quit()
    }
}
