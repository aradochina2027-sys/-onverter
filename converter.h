#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>
#include <map>

class Converter {
public:
    enum Mode { Length = 0, Mass = 1, Temperature = 2 };

    static double convert(double value, Mode mode, const QString &fromUnit, const QString &toUnit) {
        if (mode == Temperature) return convertTemp(value, fromUnit, toUnit);

        static std::map<QString, double> factors = {
            {"meters (m)", 1.0}, {"kilometers (km)", 1000.0}, {"inches (in)", 0.0254},
            {"feet (ft)", 0.3048}, {"miles (mi)", 1609.34},
            {"kilograms (kg)", 1.0}, {"pounds (lb)", 0.453592}, {"ounces (oz)", 0.0283495}
        };
        return value * (factors[fromUnit] / factors[toUnit]);
    }

private:
    static double convertTemp(double v, QString from, QString to) {
        double k;
        if (from == "Celsius (°C)") k = v + 273.15;
        else if (from == "Fahrenheit (°F)") k = (v - 32) * 5.0/9.0 + 273.15;
        else k = v;

        if (to == "Celsius (°C)") return k - 273.15;
        if (to == "Fahrenheit (°F)") return (k - 273.15) * 9.0/5.0 + 32;
        return k;
    }
};

#endif
