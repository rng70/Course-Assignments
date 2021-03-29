package Packages.Editor;

public class InterfaceFactory {
    public InfoFactory getInfoFactory(String infoType) {
        if(infoType.equalsIgnoreCase("Parser")){
            return new ParserFactory();
        }else{
            return new SyntaxHighlighterFactory();
        }
    }
}
