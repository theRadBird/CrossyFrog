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

    playerIndex = bObj_Man->AddBoundingObj(new BoundingObj(m_pMeshMngr->GetVertexList("character")));
    worldStage = new Stage(7);

    m_pCameraMngr->SetPositionTargetAndView(vector3(3.f, 6.f, 4.f), vector3(0.f, 0.f, -2.f), vector3(0.f, 1.f, 0.f), -1);

}

void AppClass::Update(void)
{
    //Update the system's time
    m_pSystem->UpdateTime();

    //Update the mesh manager's time without updating for collision detection
    m_pMeshMngr->Update();
    bObj_Man->Update();
    if (bObj_Man->collisionPass()) {
        player->IsDying();
    }
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

    bObj_Man->GetBoundingObj(playerIndex)->setModelToWorld(m_pMeshMngr->GetModelMatrix("character"));
}

void AppClass::Display(void)
{
    //clear the screen
    ClearScreen();
    worldStage->draw();

    bObj_Man->RenderAllBoundingObjects();

    m_pMeshMngr->Render(); //renders the render list

    m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
    super::Release(); //release the memory of the inherited fields
}