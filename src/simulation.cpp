/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simulation.cpp
 * Author: tg
 * 
 * Created on 27. Oktober 2016, 10:54
 */

#include "simulation.h"


simulation::simulation(unsigned int textureWidth, unsigned int textureHeight) : textureWidth(textureWidth),textureHeight(textureHeight),
        v_texData(std::vector<RendToTex>(getDataTypeSize()+1))
{
}


void simulation::init()
{
    lastSeed = rand();
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    initGUIElements();
    //init Rock
    v_texData.at(ROCK) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH ) + std::string("simulation/rock/rock_Sim"),textureWidth,textureHeight,GL_RED);
    v_texData.at(ROCK).setUniforms({{0.3,"min_therm_limit"},{3.0,"max_therm_limit"},{0.0,"threm_factor"}});
    v_texData.at(ROCK).generateParameterBar(parameterBar,"Rock",{"min=0.0 max = 10.0 step = 0.1","min=0.0 max = 10.0 step = 0.1","min=0.0 max = 5.0 step = 0.1"});
    v_texData.at(ROCK).generateActivationBar(activationBar,"Rock");

    //init Soil
    v_texData.at(SOIL) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH )  + "simulation/soil/soil_Sim",textureWidth,textureHeight,GL_RGB);
    v_texData.at(SOIL).setUniforms({{1.0,"errodeFactor"},{1.0,"soilDiffuseFactor"}});
    v_texData.at(SOIL).generateParameterBar(parameterBar,"Soil",{"min=0.0 max = 2.0 step = 0.1","min=0.0 max = 2.0 step = 0.1"});
    v_texData.at(SOIL).generateActivationBar(activationBar,"Soil");
    //init Water
    v_texData.at(WATER) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH )  + "simulation/water/water_Sim",textureWidth,textureHeight,GL_RGB);
    v_texData.at(WATER).setUniforms({{1.0,"rain"},{1.0,"evaporate"},{0.95,"sea_level"}});
    v_texData.at(WATER).generateParameterBar(parameterBar,"Water",{"min=0.0 max = 2.0 step = 0.01","min=0.0 max = 2.0 step = 0.01","min=0.0 max = 10.0 step = 0.01"});
    v_texData.at(WATER).generateActivationBar(activationBar,"Water");
        
    //init temperature 
    v_texData.at(TEMP) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH )  + "simulation/temp/temp_Sim",textureWidth,textureHeight,GL_RGB);
    v_texData.at(TEMP).setUniforms({{0.0,"latFactor"},{0.0,"sunAngle"},{2.5,"heightCooldown"},{0.0,"timeFactorTemp"},{-0.02,"rotationSpeed"},{-0.2,"DayNightFactor"}});
    v_texData.at(TEMP).generateParameterBar(parameterBar,"Temperature",{"min=-5.0 max=5.0 step= 0.1","min=-40 max=40 step = 1.0","min=1.0 max = 7.0 step = 0.1","visible=false","min=-1.0 max = 1.0 step = 0.001","min=-2.0 max = 2.0 step = 0.1"});
     v_texData.at(TEMP).generateActivationBar(activationBar,"Temperature");
     
    //init  moist
    v_texData.at(MOIST) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH )  + "simulation/moist/moist_Sim",textureWidth,textureHeight,GL_RGB);
    v_texData.at(MOIST).setUniforms({{1.0,"waterAddFactor"},{0.0,"landRemoveFactor"}});
    v_texData.at(MOIST).generateParameterBar(parameterBar,"Moist",{"min=0.0 max=5.0 step= 0.1","min=0.0 max=5.0 step = 0.1"});   
    v_texData.at(MOIST).generateActivationBar(activationBar,"Moist");    
    
    //init wind 
    v_texData.at(WIND) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH )  + "simulation/wind/wind_Sim",textureWidth,textureHeight,GL_RGB);
    v_texData.at(WIND).setUniforms({{1.0,"distorsionFaktor"},{1.0,"globelWindFaktor"},{1.0,"localPressureFaktor"},{0.0,"timeFactorWind"},{0.001,"windspeed"},{0.6,"windNoiseRoughness"},{2,"windNoiseTurbulence"}});
    v_texData.at(WIND).generateParameterBar(parameterBar,"Wind",{"min=-2.0 max=2.0 step=0.1","min=-2.0 max = 2.0 step = 0.1","min=-2.0 max = 2.0 step = 0.1","visible=false","min=-1.0 max = 1.0 step = 0.001","min=0.0 max = 8.0 step = 0.1","min=1 max = 20 step = 1"});
    v_texData.at(WIND).generateActivationBar(activationBar,"Wind");   
    windNoiseID = TextureLoader::generateNoiseTexture(textureWidth, textureHeight,rand(),v_texData.at(WIND).getParameterValue("windNoiseRoughness"),v_texData.at(WIND).getParameterValue("windNoiseTurbulence"));
    TwAddButton(parameterBar,"New Distortion",[](void* client_data)
    {
        simulation* tmpPointer = static_cast<simulation*>(client_data);
        glDeleteTextures(1, &tmpPointer->windNoiseID);
        tmpPointer->windNoiseID =  TextureLoader::generateNoiseTexture(tmpPointer->textureWidth,tmpPointer->textureHeight,rand(),tmpPointer->v_texData[WIND].getParameterValue("windNoiseRoughness"),tmpPointer->v_texData.at(WIND).getParameterValue("windNoiseTurbulence"));
    }
    ,this,"group='Wind' " );
    
    
        //init ice
    v_texData.at(ICE) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH )  + "simulation/ice/ice_Sim",textureWidth,textureHeight,GL_RGB);
    v_texData.at(ICE).setUniforms({{-0.7,"iceTemperature"}});
    v_texData.at(ICE).generateParameterBar(parameterBar,"Ice",{"min=-1.0 max=1.0 step=0.1"});
    v_texData.at(ICE).generateActivationBar(activationBar,"Ice");    
    
     //init climat 
    v_texData.at(CLIMAT) = RendToTex(sourceBuffer,destinationBuffer,std::string(SHADER_PATH )  + "simulation/climat/climat",textureWidth,textureHeight,GL_RGB);
    

    glBindVertexArray(0);
}

void simulation::initGUIElements()
{
    TwEnumVal twdisplayEnum[] = { {DataType::ROCK, "Rock"}, {DataType::SOIL, "Soil"}, {DataType::WATER, "Water"}, {DataType::TEMP, "Temp"}, 
                                  {DataType::MOIST, "Moist"}, {DataType::WIND, "Wind"}, {DataType::ICE, "Ice"}, {DataType::CLIMAT, "Climat"}};
    TwType twDisplay;
    // Defining season enum type
    twDisplay = TwDefineEnum("SeasonType", twdisplayEnum, 8);
    parameterBar = inputHandler::createNewBar("Parameters","position='8 8' size='200 500'"); 
    activationBar = inputHandler::createNewBar("Activation","position='208 8' size='200 400'"); 
    general = inputHandler::createNewBar("General","position='408 8' size='200 400'"); 
    
    TwAddVarRW(general, "Current Display", twDisplay, &currentDisplay, NULL);

   TwAddButton(general,"Restart",[](void *clientData){static_cast<simulation*>(clientData)->restart();},this,"help='Restart this world.'  ");
   TwAddButton(general,"New World",[](void *clientData){static_cast<simulation*>(clientData)->newWorld();},this,"help='Create a new World.'  ");
   TwAddButton(general,"Export",[](void *clientData){static_cast<simulation*>(clientData)->saveTextures();},this,"help='Export all textures.'  ");   
}

void simulation::initLithosphere(float sea_level, float _folding_ratio, uint32_t aggr_ratio_abs, float aggr_ratio_rel, uint32_t _max_plates, float terrainNoiseRoughness)
{
    tectonicSeaLevel = sea_level;
    this->terrainNoiseRoughness =terrainNoiseRoughness;
    ground = std::unique_ptr<lithosphere>(new lithosphere(lastSeed, textureWidth, textureHeight,tectonicSeaLevel,_folding_ratio,aggr_ratio_abs,aggr_ratio_rel,_max_plates,terrainNoiseRoughness));
   glClampColor(0x891A, GL_FALSE);
    glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
    glClampColor(0x891B, GL_FALSE);
    v_texData.at(ROCK).setTexture(ground->getTopography());
    glClampColor(0x891A, GL_TRUE);
    glClampColor(GL_CLAMP_READ_COLOR, GL_TRUE);
    glClampColor(0x891B, GL_TRUE);
    
    
//    TwAddVarRW(parameterBar,"update Rate",TW_TYPE_UINT32,&tectonicUpdate,"group='Tectonic' min=0.0 max = 100.0 step=1.0 help='Tectonic update Rate.'" );
    TwAddVarRW(parameterBar,"Noise Roughness",TW_TYPE_FLOAT,&this->terrainNoiseRoughness,"group='Tectonic' max=4 min = 0.1 step=0.1 help='set roughness of terrain' " );   
    TwAddVarRW(parameterBar,"SeaLevel",TW_TYPE_FLOAT,&tectonicSeaLevel,"group='Tectonic' max=1.0 min = 0.0 step=0.02 help='set sea Level for next terrain' " );   
   TwAddVarRW(parameterBar,"max Plates",TW_TYPE_UINT32,&ground->max_plates,"group='Tectonic' min=1.0 max = 10.0 help='Max Plate count for next start.'" );
   TwAddVarRW(parameterBar,"Folding Ratio",TW_TYPE_FLOAT,&ground->folding_ratio,"group='Tectonic' max=1.0 min=0.0 step='0.001' help='Percent of overlapping crust that is folded.' " );   
   TwAddVarRW(parameterBar,"Aggr Overlap Rel",TW_TYPE_FLOAT,&ground->aggr_overlap_rel,"group='Tectonic' max=3.00 min=0.0 step='0.03' help='% of overlapping area -> aggregation.' " );   
   TwAddVarRW(parameterBar,"Aggr Overlap Abs",TW_TYPE_UINT32,&ground->aggr_overlap_abs,"group='Tectonic' max=8000000 min=0.0 step='2000' help='# of overlapping pixels -> aggregation.' " );

    auto lam = [](void *clientData)
    {
         simulation* tmpPointer = static_cast<simulation*>(clientData);
        if(tmpPointer->enable_tectonic == false)
        {
            tmpPointer->lastSeaLevel = tmpPointer->v_texData[WATER].getParameterValue("sea_level");
            tmpPointer->v_texData.at(WATER).setParameterValue("sea_level",0.0);
            tmpPointer->v_texData.at(WATER).reset();
            tmpPointer->v_texData.at(WATER).setEnable(false);
            tmpPointer->enable_tectonic = true;            
        }
        else
        {
            tmpPointer->v_texData.at(WATER).setParameterValue("sea_level",tmpPointer->lastSeaLevel);
            tmpPointer->v_texData.at(WATER).setEnable(true);
            tmpPointer->enable_tectonic = false;          
        }

    };
   TwAddButton(activationBar,"enable/disable",lam,this,"group='Tectonic' help='Enable/Disable tectonic update.' " );
   
   TwAddButton(activationBar,"New Tectonic",[](void *clientData){static_cast<lithosphere*>(clientData)->restart();},ground.get(),"group='Tectonic' help='Generate new Plates.'" );


}
GLuint simulation::getTextureID(const DataType type)
{
    return v_texData.at(type).getSourceTexture();
}


void simulation::update()
{
    glViewport(0,0,textureWidth,textureHeight);
    glBindVertexArray(vao);
    
    
    v_texData.at(WIND).setParameterValue( "timeFactorWind",v_texData.at(WIND).getParameterValue("timeFactorWind")+v_texData.at(WIND).getParameterValue("windspeed"));
    v_texData.at(TEMP).setParameterValue( "timeFactorTemp",v_texData.at(TEMP).getParameterValue("timeFactorTemp")+v_texData.at(TEMP).getParameterValue("rotationSpeed"));
    
    //0891A = GL_CLAMP_VERTEX_COLOR, 0x891B = GL_CLAMP_FRAGMENT_COLOR
    glClampColor(0x891A, GL_FALSE);
    glClampColor(GL_CLAMP_READ_COLOR, GL_FALSE);
    glClampColor(0x891B, GL_FALSE);
    
    if(enable_tectonic)
    {
        ground->setTopography(v_texData.at(ROCK).getTexture());
        ground->update();
        v_texData.at(ROCK).setTexture(ground->getTopography());
    }
    
        //set texture bindings
    for(int i = 0; i < CLIMAT; ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, v_texData.at(i).getSourceTexture());
    }  
        glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, windNoiseID);
    
    std::for_each(v_texData.begin(), v_texData.end() ,[&](auto& data)
    {                data.update();
    });

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glActiveTexture(GL_TEXTURE7);  
    glBindTexture(GL_TEXTURE_2D, 0); 
    
    for(int i = ICE; i >= 0 ; --i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }  
    
    glClampColor(0x891A, GL_TRUE);
    glClampColor(GL_CLAMP_READ_COLOR, GL_TRUE);
    glClampColor(0x891B, GL_TRUE);
    glBindVertexArray(0);

    std::for_each(v_texData.begin(), v_texData.end(),[&](auto& data)
        {                data.swapTexture();
        });   
    
}

void simulation::restart()
{
    std::for_each(v_texData.begin(), v_texData.end() ,[&](auto& data)
    {                data.reset();
    });
    
    
   
    TwRemoveVar(parameterBar,"Noise Roughness" );   
    TwRemoveVar(parameterBar,"SeaLevel");   
   TwRemoveVar(parameterBar,"max Plates");
   TwRemoveVar(parameterBar,"Folding Ratio" );   
   TwRemoveVar(parameterBar,"Aggr Overlap Rel");   
   TwRemoveVar(parameterBar,"Aggr Overlap Abs");
   TwRemoveVar(activationBar,"New Tectonic");
   
   initLithosphere(tectonicSeaLevel,ground->folding_ratio,ground->aggr_overlap_abs,ground->aggr_overlap_rel,ground->max_plates,terrainNoiseRoughness);
}



void simulation::newWorld()
{
    lastSeed = rand();
    glDeleteTextures(1,&windNoiseID);
    windNoiseID = TextureLoader::generateNoiseTexture(textureWidth, textureHeight,rand(),v_texData.at(WIND).getParameterValue("windNoiseRoughness"),v_texData.at(WIND).getParameterValue("windNoiseTurbulence"));

    
    restart();
}



void simulation::exit()
{
    glDeleteVertexArrays(1,&vao);
    glDeleteTextures(1,&windNoiseID);
    std::for_each(v_texData.begin(), v_texData.end(),[](auto& data){data.exit();});
}

simulation::DataType simulation::getCurrentDisplay() const
{
    return currentDisplay;
}


void simulation::saveTextures()
{
    int i= 0;
    std::vector<std::string> names = {"ROCK"," SOIL "," WATER","TEMP","MOIST","WIND","ICE","Climat"};
    for(auto& val : v_texData)
    {
        ILuint index = val.prepareExport();
        TextureLoader::SaveTexture(textureWidth,textureHeight,std::string(OUTPUT_PATH) + names.at(i) + "_data.png",index);
        ++i;
        ilDeleteImage(index);
    }

}