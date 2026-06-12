class Pca9557 : public I2cDevice {
public:
    Pca9557(i2c_master_bus_handle_t i2c_bus, uint8_t addr) : I2cDevice(i2c_bus, addr) {
        ESP_LOGI("PCA9557", "Init at 0x%02X", addr);
        esp_err_t err = i2c_master_probe(i2c_bus, addr, 100);
        if (err != ESP_OK) {
            ESP_LOGW("PCA9557", "Device not found at 0x%02X, skipping", addr);
            return;
        }
        ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_transmit(i2c_device_, (uint8_t[]){0x01, 0x03}, 2, 100));
        ESP_ERROR_CHECK_WITHOUT_ABORT(i2c_master_transmit(i2c_device_, (uint8_t[]){0x03, 0xf8}, 2, 100));
    }

    void SetOutputState(uint8_t bit, uint8_t level) {
        uint8_t data = ReadReg(0x01);
        data = (data & ~(1 << bit)) | (level << bit);
        WriteReg(0x01, data);
    }
};
