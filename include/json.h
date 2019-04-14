#ifndef _JSON_H_
#define _JSON_H_

#include "struct.h"

/*
 * Update json file
 */
void write_file(Json_object json_object, Json_object json_client);

/*
 * Add data client to json file
 */
void add_client_json(Client client, Json_object json_clients);


void modify_client(Client client, Json_object json_clients, int* nb_acc);

/*
 * Parse the json file containing the client data
 */
Json_object parse_json(void);

int import_Client_idx_from_Json(char* id, int* idx);

int import_idx_from_json_with_IDA(char* id_client,char* ida,int*idx,int *idx_ida);

void get_idFromJson(int idx);

void import_Client_from_Json(int *idx,Client client_imported, int* nbAcc);

void import_Account_from_Json(int *idx, Account* tabAccount);

#endif
