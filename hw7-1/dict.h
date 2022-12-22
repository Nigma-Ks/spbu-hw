#include <stdbool.h>

struct DictionaryElement;
struct Dictionary;
enum Error;


struct Dictionary *create();

bool isKeyInDict(struct Dictionary *dictionary, int key);

enum Error getValueByKey(struct Dictionary *dictionary, int key, char **value);

enum Error add(struct Dictionary *dictionary, int key, const char *value);

enum Error delete(struct Dictionary *dictionary, int key);

void printDict(struct Dictionary *dictionary);

void deleteDict(struct Dictionary *dictionary);