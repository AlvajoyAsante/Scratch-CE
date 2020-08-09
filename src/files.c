// Anything File related is located here

#include "gui.h"
#include "files.h"
#include "runcode.h"
#include "main.h"
#include "code.h"
#include <graphx.h>

char SCR_header[4];
// struct project_t projects[30];
// int proj_amount;
// uint8_t *search_pos = NULL, type;
// char *var_name;
// char *Temp_Name;
// uint8_t y = 0;

/*void share_data(void){
	ti_CloseAll();
	
	// Header File to read data type later on
	strcpy(SCR_header, "SCR.");
	
	if(!proj.name){ // checks if name is set.
		strcpy(Temp_Name, "SCRDATAs");
		file = ti_OpenVar(Temp_Name, "w", TI_APPVAR_TYPE);
	}else{
		Temp_Name = proj.name;
		strcat(Temp_Name, "s"); 
		file = ti_OpenVar(Temp_Name, "w", TI_APPVAR_TYPE);
	}
	
	// ti_Write(&SCR_header, sizeof(SCR_header), 1, file); // TI header so can read later on.
	
	ti_Write(&proj, sizeof(proj), 1, file); // projram Info
	ti_Write(&data, sizeof(data), 1, file); // Code 
	ti_Write(&stage, sizeof(stage), 1, file); // stage info
	ti_Write(&costumes, sizeof(costumes), 1, file);

	//ti_SetArchiveStatus(true, file);
	
	ti_Close(file);
}*/

void data_save(void){
	ti_CloseAll();
	strcpy(SCR_header, "SCR.");

	if (!proj.name){
		file = ti_OpenVar("SCRPROJ", "w", TI_APPVAR_TYPE);
	}else{
		file = ti_OpenVar(proj.name, "w", TI_APPVAR_TYPE);
	}
	
	// ti_Write(&SCR_header, sizeof(SCR_header), 1, file); // Header
	ti_Write(&proj, sizeof(proj), 1, file); // program info
	ti_Write(&data, sizeof(data), 1, file); // code 
	ti_Write(&stage, sizeof(stage), 1, file); // stage data 
	ti_Write(&costumes, sizeof(costumes), 1, file);
	ti_SetArchiveStatus(true, file);
	
	ti_Close(file);
	gfx_PopupMessage("Message:","Project data saved.", 1, gfx_green);
}

void load_data(void){
	ti_CloseAll();
	
	if (!proj.name){
		file = ti_OpenVar("SCRPROJ", "r", TI_APPVAR_TYPE);
	}else{
		file = ti_OpenVar(proj.name, "r", TI_APPVAR_TYPE);
	}
		
	// ti_Read(&SCR_header, sizeof(SCR_header), 1, file); // Header
	ti_Read(&proj, sizeof(proj), 1, file); // program Data
	ti_Read(&data, sizeof(data), 1, file); // Code and CodeX
	ti_Read(&stage, sizeof(stage), 1, file); // stage info
	ti_Read(&costumes, sizeof(costumes), 1, file);
	ti_SetArchiveStatus(true, file);
	
	ti_Close(file);
	
	return;
}

/*void find_SCR_files(void){
	// Dectect any file with "SCR."
	
	strcpy(SCR_header, "SCR.");
	
	ti_CloseAll();
	
	while ((var_name = ti_DetectAny(&search_pos, SCR_header, &type)) != NULL){
        if (type == TI_APPVAR_TYPE){
			strcpy(projects[y].name, var_name);
			y++; // changes Y pos
			proj_amount++;
        }
    }
	
	// check if there was not any found
	if (proj_amount == 0) error = 1;
	
	
	ti_Close(file);
}

void load_extern_sprites(void){
	uint16_t *dataPtr;
	size_t *dataSize;
	ti_CloseAll();
	
	file = ti_OpenVar("SCREXTN", "r", TI_APPVAR_TYPE); // find sprite appvar
	
	if (!file){
		// throw an error
		return;
	}
	
	dataPtr = ti_GetDataPtr(file);
	ti_Read(&dataPtr, ti_GetSize(file), 1, file);
	
	ti_Close(file);
	return;
}*/