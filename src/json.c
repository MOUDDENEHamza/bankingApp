#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"

/*
 * Parse the json file containing the client data
 *
void parse_json(Client head) {
	FILE *fp;
        char buffer[1024], str1[1024], str2[1024];
        struct json_object *parsed_json;
        struct json_object *list;
        struct json_object *item;
        struct json_object *id, *passwd, *last_name, *first_name, *mail, *phone, *birthday, *address;
        size_t len;
        size_t i;
        fp = fopen("data/account_list.json","r");
        fread(buffer, 1024, 1, fp);
	fclose(fp);
        parsed_json = json_tokener_parse(buffer);
        json_object_object_get_ex(parsed_json, "clients", &list);
        len = json_object_array_length(list);
        for(i = 0; i < len; i++) {
                item = json_object_array_get_idx(list, i);
                id = json_object_array_get_idx(item, 0);
		passwd = json_object_array_get_idx(item, 1);
		last_name = json_object_array_get_idx(item, 2);
                first_name = json_object_array_get_idx(item, 3);
                mail = json_object_array_get_idx(item, 4);
                phone = json_object_array_get_idx(item, 5);
                birthday = json_object_array_get_idx(item, 6);
                address = json_object_array_get_idx(item, 7);
		strcpy(str1, json_object_get_string(id));
		strcpy(str2, json_object_get_string(passwd));
	}
	head = append(head, str1, str2);
	traverse(head);
}
*/
