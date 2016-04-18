#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
    super::InitWindow("LERP"); // Window Name

                               // Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
                               //if this line is in Init Application it will depend on the .cfg file, if it
                               //is on the InitVariables it will always force it regardless of the .cfg
    m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
    m_v3Rotation = vector3(0.0f);

    //Set the camera at a position other than the default
    m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 12.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

    //Load a model onto the Mesh manager
    m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
}

void AppClass::Update(void)
{
    //Update the system's time
    m_pSystem->UpdateTime();

    //Update the mesh manager's time without updating for collision detection
    m_pMeshMngr->Update();

    //First person camera movement
    if (m_bFPC == true)
        CameraRotation();

    //Call the arcball method
    ArcBall();

    //Lets us know how much time has passed since the last call
    double fTimeSpan = m_pSystem->LapClock();

    //cumulative time
    static double fRunTime = 0.0f;
    fRunTime += fTimeSpan;

    matrix4 mOrientation = glm::rotate(IDENTITY_M4, m_v3Rotation.x, vector3(1.0f, 0.0f, 0.0f));
    mOrientation = mOrientation * glm::rotate(IDENTITY_M4, m_v3Rotation.y, vector3(0.0f, 1.0f, 0.0f));
    mOrientation = mOrientation * glm::rotate(IDENTITY_M4, m_v3Rotation.z, vector3(0.0f, 0.0f, 1.0f));

    vector3 v3Start(0.0f, 0.0f, 0.0f);
    vector3 v3End(0.0f, 90.0f, 0.0f);
    static float fDifference = 0.0f;
    fDifference += 0.1f;
    fDifference = MapValue(static_cast<float>(fRunTime), 0.0f, 10.0f, 0.0f, 1.0f);

    float fPosition = glm::lerp(v3Start, v3End, fDifference).y;

    mOrientation = glm::rotate(IDENTITY_M4, fPosition, vector3(0.0f, 1.0f, 0.0f));

    m_pMeshMngr->SetModelMatrix(mOrientation, "Steve");

    //Adds all loaded instance to the render list
    m_pMeshMngr->AddInstanceToRenderList("ALL");

    //Indicate the FPS
    int nFPS = m_pSystem->GetFPS();
    //print info into the console
    //printf("FPS: %d            \r", nFPS);//print the Frames per Second
    //Print info on the screen
    m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

    m_pMeshMngr->Print("FPS:");
    m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
    //clear the screen
    ClearScreen();

    //Render the grid based on the camera's mode:
    switch (m_pCameraMngr->GetCameraMode())
    {
    default: //Perspective
        m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
        break;
    case CAMERAMODE::CAMROTHOX:
        m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
        break;
    case CAMERAMODE::CAMROTHOY:
        m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
        break;
    case CAMERAMODE::CAMROTHOZ:
        m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
        break;
    }

    m_pMeshMngr->Render(); //renders the render list

    m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
    super::Release(); //release the memory of the inherited fields
}