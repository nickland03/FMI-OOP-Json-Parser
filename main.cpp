#include "src/JsonParser/JsonParser.h"

int main() {
    // read json from file and load it into memory
    JsonParser jp("example.json");

    // print the content in a readable way
//    jp.print();

    // delete value by key in a given path
    jp.remove("hehe/name");

    // print the content in a readable way
    jp.print();

    // list values which correspond to a given key
//    jp.list("name");

    return 0;
}
