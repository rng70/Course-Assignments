package Package.Builder;

import Package.AdditionalController.Buttons;
import Package.Controller.Arduino;
import Package.Display.LED;
import Package.Identification.RFIDCard;
import Package.InternetConnection.InternetConnection;
import Package.Storage.SDCardStorage;
import Package.WeightMeasurement.WeightMeasurement;

public class ArduinoMega implements Builder {
  Hardware hardware = new Hardware();

  @Override
  public void makeController() {
    hardware.makeController(new Arduino());
  }

  @Override
  public void setWeightMeasurementTool(WeightMeasurement tool) {
    hardware.setWeightMeasurementTool(tool);
  }

  @Override
  public void setIdentifier() {
    hardware.setIdentifier(new RFIDCard());
  }

  @Override
  public void setStorageMedium() {
    hardware.setStorage(new SDCardStorage());
  }

  @Override
  public void setDisplay() {
    hardware.setDisplay(new LED());
  }

  @Override
  public void setInternetConnectivity(InternetConnection ic) {
    hardware.setInternetConnection(ic);
  }

  public void setAdditionalControllers() {
    hardware.setAdditionalController(new Buttons());
  }
  @Override
  public Hardware getHardware() {
      return this.hardware;
  }
}
