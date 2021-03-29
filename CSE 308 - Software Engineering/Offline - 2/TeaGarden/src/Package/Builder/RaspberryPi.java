package Package.Builder;

import Package.Controller.RaspberryPI;
import Package.Display.TouchScreen;
import Package.Identification.NFCCard;
import Package.Storage.PiStorage;
import Package.WeightMeasurement.WeightMeasurement;
import Package.InternetConnection.InternetConnection;
import Package.AdditionalController.TouchAsAdditionalController;

public class RaspberryPi implements Builder {

  Hardware hardware = new Hardware();

  @Override
  public void makeController() {
    hardware.makeController(new RaspberryPI());
  }

  @Override
  public void setWeightMeasurementTool(WeightMeasurement tool) {
    hardware.setWeightMeasurementTool(tool);
  }

  @Override
  public void setIdentifier() {
    hardware.setIdentifier(new NFCCard());
  }

  @Override
  public void setStorageMedium() {
    hardware.setStorage(new PiStorage());
  }

  @Override
  public void setDisplay() {
    hardware.setDisplay(new TouchScreen());
  }

  @Override
  public void setInternetConnectivity(InternetConnection ic) {
    hardware.setInternetConnection(ic);
  }

  public void setAdditionalControllers() {
    hardware.setAdditionalController(new TouchAsAdditionalController());
  }

  @Override
  public Hardware getHardware() {
    return this.hardware;
  }
}
