#ifndef __DICT_MANIP_H__
#define __DICT_MANIP_H__

struct Dictionary;

bool read_dict(Dictionary*, char*, int&);
void add_word(Dictionary*, int&);
void delete_word(Dictionary*, int&);
void eng_to_rus(Dictionary*, int);
void rus_to_eng(Dictionary*, int);
void print_dict(Dictionary*, int);
void write_dict(Dictionary*, int, char*);

void sort_dict(Dictionary*, int);
char* cut(char[]);

#endif //__DICT_MANIP_H__