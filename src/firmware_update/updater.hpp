#pragma once

#include <pins.hpp>

#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <Update.h>

enum class UpdateStatus {
    NO_CARD,
    FILE_ERROR,
    INSUFFICIENT_SPACE,
    UPDATE_ERROR,
    UPDATE_OK,
};

UpdateStatus perform_update(Stream &update_source, size_t update_size) {
    if (!Update.begin(update_size)) {
        Serial.println("Not enough space to begin update.");
        return UpdateStatus::INSUFFICIENT_SPACE;
    }

    size_t written = Update.writeStream(update_source);
    if (written == update_size) {
        Serial.println("Written : " + String(written) + " bytes successfully.");
    } else {
        Serial.println("Written only : " + String(written) + " bytes of " + String(update_size) + ".");
    }

    if (!Update.end()) {
        Serial.println("Error Occurred. Error ID: " + String(Update.getError()));
        return UpdateStatus::UPDATE_ERROR;
    }
    if (Update.isFinished()) {
        Serial.println("Update successfully completed.");
        return UpdateStatus::UPDATE_OK;
    } else {
        Serial.println("Update not finished. Something went wrong!");
        return UpdateStatus::UPDATE_ERROR;
    }
}

UpdateStatus update_from_fs(fs::FS &fs) {
    File update_bin = fs.open("/update.bin");
    if (!update_bin) {
        Serial.println("Could not load update.bin from sd root.");
        return UpdateStatus::FILE_ERROR;
    }
    if (update_bin.isDirectory()) {
        Serial.println("Error, update.bin is not a file.");
        update_bin.close();
        return UpdateStatus::FILE_ERROR;
    }

    size_t update_size = update_bin.size();

    if (update_size > 0) {
        Serial.println("Starting update process.");
        perform_update(update_bin, update_size);
    } else {
        Serial.println("Error, file is empty.");
        update_bin.close();
        return UpdateStatus::FILE_ERROR;
    }

    update_bin.close();

    // on finish, remove the binary from sd card to indicate success of the process
    fs.remove("/update.bin");

    return UpdateStatus::UPDATE_OK;
}

UpdateStatus attempt_update() {
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("Card Mount Failed.");
        return UpdateStatus::NO_CARD;
    }

    sdcard_type_t cardType = SD.cardType();

    if (cardType == CARD_NONE || cardType == CARD_UNKNOWN) {
        Serial.println("SD card not attached or not supported.");
        return UpdateStatus::NO_CARD;
    }
    return update_from_fs(SD);
}
