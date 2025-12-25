#pragma once
#include <QObject>
#include <QString>
#include <cmath>
#include <iomanip>
#include <sstream>

class Converter : public QObject {
  Q_OBJECT
  public:
  explicit Converter(QObject *parent = nullptr) : QObject(parent) {}
  Q_INVOKABLE QString convert(int index, double value) {
    double res = 0.0;
    QString unit;
    switch (index) {
      case 0:
        res = (value * 9.0 / 5.0) + 32.0; unit = "°F"; break;
      case 1:
        res = value + 273.15; unit = "K"; break;
      case 2:
        res = value * 4.0 / 5.0; unit = "°R"; break;
      case 3:
        res = (value - 32.0) * 5.0 / 9.0; unit = "°C"; break;
      case 4:
        res = (value - 32.0) * 5.0 / 9.0 + 273.15; unit = "K"; break;
      case 5:
        res = (value - 32.0) * 4.0 / 9.0; unit = "°R"; break;
      case 6:
        res = value - 273.15; unit = "°C"; break;
      case 7:
        res = (value - 273.15) * 9.0 / 5.0 + 32.0; unit = "°F"; break;
      case 8:
        res = (value - 273.15) * 4.0 / 5.0; unit = "°R"; break;
      case 9:
        res = value * 5.0 / 4.0; unit = "°C"; break;
      case 10:
        res = (value * 9.0 / 4.0) + 32.0; unit = "°F"; break;
      case 11:
        res = (value * 5.0 / 4.0) + 273.15; unit = "K"; break;
      default:
        return QStringLiteral("Pilihan tidak valid");
    }
    std::ostringstream ss;
    double intpart;
    if (std::modf(res, &intpart) == 0.0) {
      ss << static_cast<long long>(std::llround(res));
    } else {
      ss << std::fixed << std::setprecision(4) << res;
    }
    return QString::fromStdString(ss.str()) + " " + unit;
  }
};
