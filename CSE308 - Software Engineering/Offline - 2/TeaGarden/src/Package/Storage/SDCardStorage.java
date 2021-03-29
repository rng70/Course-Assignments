package Package.Storage;

public class SDCardStorage implements Storage{
    @Override
    public void showStorageMessage(){
        System.out.println("Storage is interfaced with SD card");
    }
}
