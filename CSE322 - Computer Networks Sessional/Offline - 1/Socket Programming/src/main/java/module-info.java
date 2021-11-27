module com.example.socketprogramming {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens rng70.socketprogramming to javafx.fxml;
    exports rng70.socketprogramming;

    requires java.desktop;
}