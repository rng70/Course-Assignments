package Packages.Editor;

import Packages.Aesthetics.*;
import Packages.Parser.Parser;

public class SyntaxHighlighterFactory implements InfoFactory{
    @Override
    public Aesthetics getHighlighter(String highlighterFileExtension){
        if(highlighterFileExtension.equalsIgnoreCase("c")){
            return new CHighlighter();
        }else if(highlighterFileExtension.equalsIgnoreCase("cpp")){
            return new CPPHighlighter();
        }else{
            return new PyHighlighter();
        }
    }
    @Override
    public Parser getParser(String parserFileExtension){
        return null;
    }
}
