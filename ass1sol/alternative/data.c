#include "data.h"


data_t* read_data_field(FILE* file_in){
    data_t* ret_val = (data_t*) malloc (sizeof(data_t));
    assert(ret_val);

    //fgets(buffer, MAX_BUF_LEN + 1, file_in);
    if(fscanf(file_in, "%d,", &(ret_val->footpath_id)) != 1){
        free(ret_val);
        ret_val = NULL;
        return ret_val;
    }
    //Some defualt value for DEBUGING
    ret_val->a = ret_val->footpath_id;
    ret_val->address = read_string(file_in);
    ret_val->clue_sa = read_string(file_in); 
    ret_val->asset_type = read_string(file_in); 
    fscanf(file_in, "%lf,", &(ret_val->deltaz));
    fscanf(file_in, "%lf,", &(ret_val->distance));
    fscanf(file_in, "%lf,", &(ret_val->grade1in));
    fscanf(file_in, "%d.0,", &(ret_val->mcc_id));
    fscanf(file_in, "%d.0,", &(ret_val->mccid_int));
    fscanf(file_in, "%lf,", &(ret_val->rlmax));
    fscanf(file_in, "%lf,", &(ret_val->rlmin));
    ret_val->segside = read_string(file_in); 
    fscanf(file_in, "%d.0,", &(ret_val->statusid));
    fscanf(file_in, "%d.0,", &(ret_val->streetid));
    fscanf(file_in, "%d.0,", &(ret_val->street_group));
    fscanf(file_in, "%lf,", &(ret_val->start_lat));
    fscanf(file_in, "%lf,", &(ret_val->start_lon));
    fscanf(file_in, "%lf,", &(ret_val->end_lat));
    fscanf(file_in, "%lf", &(ret_val->end_lon));
    return ret_val;  
}

char* read_string(FILE* file_in){
    char buffer[MAX_STR_LEN + 1];
    int i = 0;
    fscanf(file_in, "%c", &buffer[i]);

    if(buffer[0] == '"'){
        for(i = 0; (fscanf(file_in, "%c", &buffer[i]) == 1) && (buffer[i] != '"'); i++);
        char delimit = fgetc(file_in);
        assert(delimit == ',');
    } else if(buffer[0] == ','){
        char* ret_val = (char*)calloc(1,sizeof(char));
        assert(ret_val);
        *ret_val='\0';
        return ret_val;
    } else {
        for(i = 1; (fscanf(file_in, "%c", &buffer[i]) == 1) && (buffer[i] != ','); i++);
    }
    buffer[i] = '\0';
    return strdup(buffer);
}

void print_data(FILE* file_out){
    printf("Printing data...");
}

void print_field(data_t* value, FILE* file_out){
    fprintf(file_out,"--> footpath_id: %d || address: %s || clue_sa: %s || asset_type: %s || deltaz: %.2lf || distance: %.2lf || grade1in: %.1lf || mcc_id: %d || mccid_int: %d || rlmax: %.2lf || rlmin: %.2lf || segside: %s || statusid: %d || streetid: %d || street_group: %d || start_lat: %.6lf || start_lon: %.6lf || end_lat: %.6lf || end_lon: %.6lf ||\n",
    value->footpath_id,
    value->address,
    value->clue_sa,
    value->asset_type,
    value->deltaz,
    value->distance,
    value->grade1in,
    value->mcc_id,
    value->mccid_int,
    value->rlmax,
    value->rlmin,
    value->segside,
    value->statusid,
    value->streetid,
    value->street_group,
    value->start_lat,
    value->start_lon,
    value->end_lat,
    value->end_lon);
}

int is_address_match(char* addr1, char* addr2){
    if(strcmp(addr1,addr2) == 0){
        return 1;
    }
    return 0;
}

data_t* best_grade1in(data_t* data1, data_t* data2, double value){
    if(fabs(data1->grade1in-value) < fabs(data2->grade1in-value)){
        return data1;
    }
    return data2;
}
void free_data(data_t* data){
    free(data->address);
    free(data->clue_sa);
    free(data->asset_type);
    free(data->segside);
    free(data);
}
