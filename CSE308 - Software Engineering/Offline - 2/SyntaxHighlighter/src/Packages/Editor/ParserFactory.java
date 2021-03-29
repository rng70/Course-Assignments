package Packages.Editor;

import Packages.Parser.*;
import Packages.Aesthetics.Aesthetics;

public class ParserFactory implements InfoFactory{
    @Override
    public Parser getParser(String parserFileExtension){
        if(parserFileExtension.equalsIgnoreCase("c")){
            return new CParser();
        }else if(parserFileExtension.equalsIgnoreCase("cpp")){
            return new CPPParser();
        }else {
            return new PyParser();
        }
    }
    @Override
    public Aesthetics getHighlighter(String highlighterFileExtension){
        return null;
    }
}
