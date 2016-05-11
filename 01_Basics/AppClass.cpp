#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
    super::InitWindow("LERP"); // Window Name

                               // Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
                               //if this line is in Init Application it will depend on the .cfg file, if it
                               //is on the InitVariables it will always force it regardless of the .cfg
    m_v4ClearColor = vector4(.9f, .9f, .9f, 0.0f);
}

void AppClass::InitVariables(void)
{
    srand(time(0));
    m_v3Rotation = vector3(0.0f);

    //Set the camera at a position other than the default
    m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 12.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

    //Load a model onto the Mesh manager
    m_pMeshMngr->LoadModel("Crossy\\character.obj", "character");
    m_pMeshMngr->LoadModel("Crossy\\obstacle1.obj", "obstacle");
    m_pMeshMngr->LoadModel("Crossy\\mover.obj", "mover");
    bObj_Man = BoundingObjectManagerSingleton::GetInstance();

    player = new Character();
    obst1 = new Obstacle();

    obst1->setPosition(vector3(0.f, 0.6f, -1.f));
    obst1->setRadius(0.75f);

    worldStage = new Stage(7);

    playerIndex = bObj_Man->AddBoundingObj(new BoundingObj(m_pMeshMngr->GetVertexList("character")));
    obstIndex = bObj_Man->AddBoundingObj(new BoundingObj(m_pMeshMngr->GetVertexList("obstacle")));


    m_pCameraMngr->SetPositionTargetAndView(vector3(3.f, 6.f, 4.f), vector3(0.f, 0.f, -2.f), vector3(0.f, 1.f, 0.f), -1);

}

void AppClass::Update(void)
{
    //Update the system's time
    m_pSystem->UpdateTime();

    //Update the mesh manager's time without updating for collision detection
    m_pMeshMngr->Update();
    bObj_Man->Update();
    //First person camera movement
    if (m_bFPC == true)
        CameraRotation();

    //Call the arcball method
    ArcBall();

    //Lets us know how much time has passed since the last call
    fTimeSpan = m_pSystem->LapClock();

    //cumulative time
    static double fRunTime = 0.0f;
    fRunTime += fTimeSpan;

    /// Updates the stage
    worldStage->update(fTimeSpan);

    player->Update(fTimeSpan);

    //m_pMeshMngr->SetModelMatrix(glm::translate(playerMove), "character");

    bObj_Man->GetBoundingObj(playerIndex)->setModelToWorld(m_pMeshMngr->GetModelMatrix("character"));

// vector3 temp = mover1->getPosition();
    //bObj_Man->GetBoundingObj(obstIndex)->setModelToWorld(matrix4(IDENTITY_M4* vector4(temp.x, temp.y, temp.z,1.0f)));
    
    if(bObj_Man->CheckCollision(0, 1)){
        bObj_Man->SetBoundingObjectColor(1, REGREEN);
    }
    //Adds all loaded instance to the render list
    //m_pMeshMngr->AddInstanceToRenderList("ALL");

    //Indicate the FPS
    //int nFPS = m_pSystem->GetFPS();
    //print info into the console
    //printf("FPS: %d            \r", nFPS);//print the Frames per Second
    //Print info on the screen
    //m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

    //m_pMeshMngr->Print("FPS:");
    //m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
    //clear the screen
    ClearScreen();
    worldStage->draw();

    bObj_Man->RenderAllBoundingObjects();
    //Render the grid based on the camera's mode:
    //switch (m_pCameraMngr->GetCameraMode())
    //{
    //default: //Perspective
    //    m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ); //renders the XY grid with a 100% scale
    //    break;
    //case CAMERAMODE::CAMROTHOX:
    //    m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
    //    break;
    //case CAMERAMODE::CAMROTHOY:
    //    m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
    //    break;
    //case CAMERAMODE::CAMROTHOZ:
    //    m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
    //    break;
    //}

    m_pMeshMngr->Render(); //renders the render list

    m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
    super::Release(); //release the memory of the inherited fields
}