#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;

class IDevice {
public:
    virtual ~IDevice() = default;
    virtual void power() = 0;
    virtual void plus() = 0;
    virtual void minus() = 0;
    virtual void next() = 0;
    virtual void prev() = 0;
    virtual void showInfo() const = 0;
};

class TV : public IDevice {
public:
    TV(int maxVolume, int maxChannels)
        : isOn(false), volume(0), channel(1), maxVolume(maxVolume), maxChannels(maxChannels) {}

    void power() override {
        isOn = !isOn;
        cout << "TV is " << (isOn ? "ON" : "OFF") << endl;
    }

    void plus() override {
        if (isOn && volume < maxVolume) {
            volume++;
            cout << "TV volume: " << volume << endl;
        }
    }

    void minus() override {
        if (isOn && volume > 0) {
            volume--;
            cout << "TV volume: " << volume << endl;
        }
    }

    void next() override {
        if (isOn) {
            channel = (channel % maxChannels) + 1;
            cout << "TV channel: " << channel << endl;
        }
    }

    void prev() override {
        if (isOn) {
            channel = (channel - 2 + maxChannels) % maxChannels + 1;
            cout << "TV channel: " << channel << endl;
        }
    }

    void showInfo() const override {
        cout << "TV [" << (isOn ? "ON" : "OFF") << "], Volume: " << volume
            << ", Channel: " << channel << endl;
    }

private:
    bool isOn;
    int volume;
    int channel;
    int maxVolume;
    int maxChannels;
};

class AirConditioner : public IDevice {
public:
    enum Mode { Cooling, Heating, Turbo, Sleep };

    AirConditioner(int minTemp, int maxTemp)
        : isOn(false), temperature(minTemp), mode(Cooling), minTemp(minTemp), maxTemp(maxTemp) {}

    void power() override {
        isOn = !isOn;
        cout << "AirConditioner is " << (isOn ? "ON" : "OFF") << endl;
    }

    void plus() override {
        if (isOn && temperature < maxTemp) {
            temperature++;
            cout << "AirConditioner temperature: " << temperature << endl;
        }
    }

    void minus() override {
        if (isOn && temperature > minTemp) {
            temperature--;
            cout << "AirConditioner temperature: " << temperature << endl;
        }
    }

    void next() override {
        if (isOn) {
            mode = static_cast<Mode>((mode + 1) % 4);
            showMode();
        }
    }

    void prev() override {
        if (isOn) {
            mode = static_cast<Mode>((mode - 1 + 4) % 4);
            showMode();
        }
    }

    void showInfo() const override {
        cout << "AirConditioner [" << (isOn ? "ON" : "OFF") << "], Temperature: "
            << temperature << ", Mode: " << modeToString() << endl;
    }

private:
    bool isOn;
    int temperature;
    Mode mode;
    int minTemp;
    int maxTemp;

    void showMode() const {
        cout << "AirConditioner mode: " << modeToString() << endl;
    }

    string modeToString() const {
        switch (mode) {
        case Cooling: return "Cooling";
        case Heating: return "Heating";
        case Turbo: return "Turbo";
        case Sleep: return "Sleep";
        default: return "Unknown";
        }
    }
};

class SmartRemote {
public:
    void addDevice(IDevice* device) {
        devices.push_back(device);
    }

    void switchDevice(int index) {
        if (index >= 0 && index < devices.size()) {
            currentDevice = devices[index];
            cout << "Switched to device " << index + 1 << endl;
            currentDevice->showInfo();
        }
        else {
            cout << "Invalid device index" << endl;
        }
    }

    void power() {
        if (currentDevice) currentDevice->power();
    }

    void plus() {
        if (currentDevice) currentDevice->plus();
    }

    void minus() {
        if (currentDevice) currentDevice->minus();
    }

    void next() {
        if (currentDevice) currentDevice->next();
    }

    void prev() {
        if (currentDevice) currentDevice->prev();
    }

    void showInfo() const {
        if (currentDevice) currentDevice->showInfo();
    }

private:
    vector<IDevice*> devices;
    IDevice* currentDevice = nullptr;
};

int main() {
    TV tv(100, 10);
    AirConditioner ac(16, 25);

    SmartRemote remote;
    remote.addDevice(&tv);
    remote.addDevice(&ac);

    remote.switchDevice(0);
    remote.power();
    remote.plus();
    remote.next();
    remote.showInfo();

    remote.switchDevice(1);
    remote.power();
    remote.plus();
    remote.next();
    remote.showInfo();

    return 0;
}
