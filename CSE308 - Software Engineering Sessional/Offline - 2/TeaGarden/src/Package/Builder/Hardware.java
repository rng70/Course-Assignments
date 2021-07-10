package Package.Builder;

import Package.AdditionalController.AdditionalController;
import Package.Controller.Controller;
import Package.Display.Display;
import Package.Identification.Identification;
import Package.InternetConnection.InternetConnection;
import Package.Storage.Storage;
import Package.WeightMeasurement.WeightMeasurement;

public class Hardware {
  Storage storage = null;
  Display display = null;
  Controller controller = null;
  Identification identification = null;
  WeightMeasurement weightMeasurement = null;
  InternetConnection internetConnection = null;
  AdditionalController additionalController = null;

  public void setStorage(Storage s) {
    this.storage = s;
  }

  public void showHardwareComponents() {
    display.showDisplayInfo();
    storage.showStorageMessage();
    identification.showCredentials();
    controller.showControllerMessage();
    internetConnection.showConnectionType();
    additionalController.showControllerInfo();
    weightMeasurement.showWeightMeasurementInfo();
  }

  public void setDisplay(Display display) {
    this.display = display;
  }

  public void makeController(Controller controller) {
    this.controller = controller;
  }

  public void setInternetConnection(InternetConnection i) {
    this.internetConnection = i;
  }

  public void setIdentifier(Identification identification) {
    this.identification = identification;
  }

  public void setAdditionalController(AdditionalController a) {
    this.additionalController = a;
  }

  public void setWeightMeasurementTool(WeightMeasurement weightMeasurement) {
    this.weightMeasurement = weightMeasurement;
  }
}
