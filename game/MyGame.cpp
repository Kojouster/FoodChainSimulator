#include "stdafx.h"
#include "MyGame.h"
#include <iostream>

using std::cout;
using std::endl;

CMyGame::CMyGame(void)
	: grass("fieldTexture.png"),
	  rabbit(50, 550, 20, 40, "rabbit1.png", CColor::Green(128), 0),        // rabbit is mouse sprite
	  fox(750, 50, 40, 50, "fox.png", CColor::Green(128), 0),
	  apple(150,400,20,20,"apple.png", CColor::Green(128), 0),            //apple is actually a ladyBug sprite
	  wolf(350,50,40,60,"wolf.png",CColor::Green(128), 0),              // wolf sprite
	  carrot(50,100,20,20,"carrot.png", CColor::Green(128), 0),
	  rHouse(600,500,70,70,"rHouse.png", CColor::Green(128), 0),      // rabits house,fox is scared of loud noises from the house
	  trap(1200,600,50,50,"Trap.png", CColor::Green(128), 0),        // wolf and mouse trap
	  trap1(100, 60, 50, 50, "Trap.png", CColor::Green(128), 0),    // wolf and mouse trap2
	  trap2(1200, 50, 50, 50, "Trap.png", CColor::Green(128), 0),   // wolf and mouse trap3
	  trap3(100, 600, 50, 50, "Trap.png", CColor::Green(128), 0),   // wolf and mouse trap4

	fTrap(1200,300,40,40,"fTrap.png", CColor::Green(128), 0), //fox trap 
	fTrap1 (100,300,40,40, "fTrap.png", CColor::Green(128), 0), // fox trap2
	 Bush (350, 50, 70, 70,"Bush.png", CColor::Green(128), 0)





{

}

CMyGame::~CMyGame(void)
{
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{

	

	
	float foxSpeed = 400;
	float foxWanderSpeed = 410;
	float rabbitSpeed = 410;
	float rabbitWanderSpeed = 450;
	float appleSpeed = 415;
	float carrotSpeed = 380;
	float carrotWanderSpeed = 340;
	float appleWanderSpeed = 450;
	float wolfSpeed = 350;

	double houseRadius = 10;




// Steering Forces
	CVector steerFox, steerRabbit, steerApple, steerWolf,steerCarrot,rabbitHide;

	
	
	if (Distance(rHouse.GetPosition(), fox.GetPosition()) < 115)    //fox avoiding house full of humans

	{

		steerFox = fox.flee(rHouse.GetPosition(), foxSpeed);
	}
	else if (Distance(fTrap.GetPosition(), fox.GetPosition()) < 115)    // fox avoiding fox trap
	{
		steerFox = fox.flee(fTrap.GetPosition(), foxSpeed);
	}

	else if (Distance(fTrap1.GetPosition(), fox.GetPosition()) < 115)  // fox avoiding fox trap1
	{
		steerFox = fox.flee(fTrap1.GetPosition(), foxSpeed);
	}


	else if (Distance(wolf.GetPosition(), fox.GetPosition()) < 150)  // fox avoiding wolf when static
	{
		steerFox = fox.flee(wolf.GetPosition(), foxSpeed);
	}
	else if (Distance(rabbit.GetPosition(), fox.GetPosition()) < 800 && rabbit.IsDeleted()==false) //fox seeking mouse when he is still alive
	{

		steerFox = fox.seek(rabbit.GetPosition(), foxSpeed);
	}

    if (Distance(rabbit.GetPosition(), apple.GetPosition()) < 250) // lady bug fleeing from mouse
	{
		steerApple = apple.flee(rabbit.GetPosition(), appleSpeed);
	}


	if (Distance(trap.GetPosition(), rabbit.GetPosition()) < 120 ) //mouse avoiding trap

	{
		steerRabbit = rabbit.flee(trap.GetPosition(), rabbitSpeed);

	}
	else if (Distance(trap1.GetPosition(), rabbit.GetPosition()) < 120)//mouse avoiding trap

	{
		steerRabbit = rabbit.flee(trap1.GetPosition(), rabbitSpeed);
	}
	else if (Distance(trap2.GetPosition(), rabbit.GetPosition()) < 120)//mouse avoiding trap

	{
		steerRabbit = rabbit.flee(trap2.GetPosition(), rabbitSpeed);
	}
	else if (Distance(trap3.GetPosition(), rabbit.GetPosition()) < 120)//mouse avoiding trap

	{
		steerRabbit = rabbit.flee(trap3.GetPosition(), rabbitSpeed);
	}
	else if (Distance(fox.GetPosition(), rabbit.GetPosition()) < 250)// mouse fleeing from fox

	{
		steerRabbit=rabbit.flee(fox.GetPosition(), rabbitSpeed);

	}
    else if (Distance(apple.GetPosition(), rabbit.GetPosition()) < 800) // mouse is looking for the ladybug

	{
		steerRabbit = rabbit.seek(apple.GetPosition(), rabbitSpeed);
	}
	
	if (rabbit.HitTest(&apple)) //deleting lady bug when eaten
	{
		apple.Delete();
		apple.IsDeleted() == true;
		
	}
	if (apple.IsDeleted() == true && Distance(fox.GetPosition(), rabbit.GetPosition()) < 700 )// mouse is full and returning to the house to hide from fox
	{
		
		steerRabbit = rabbit.seek(rHouse.GetPosition(), rabbitSpeed);
		carrot.Delete();
		carrot.IsDeleted() == true;
	}

	else if (carrot.IsDeleted() == true && Distance(fox.GetPosition(), rabbit.GetPosition()) < 300)
	{
		steerRabbit = rabbit.flee(fox.GetPosition(), rabbitSpeed);
	}
	if (carrot.IsDeleted() == true && rabbit.HitTest(&rHouse))

	{
		Bush.Delete();
		Bush.IsDeleted() == true;
		rabbit.Delete();
		rabbit.IsDeleted() == true;
	}
	else if (fox.HitTest(&rabbit))  // unlucky mouse dint make it 
	{

		rabbit.Delete();
		rabbit.IsDeleted() == true;
		apple.Delete();
		apple.IsDeleted() == true;
		Bush.Delete();
		Bush.IsDeleted() == true;
	}
	if (rabbit.IsDeleted() == true && Distance(fox.GetPosition(), wolf.GetPosition()) < 800) // wolf is hungry and seeking the fox

	{
		steerWolf = wolf.seek(fox.GetPosition(), wolfSpeed);
		
	}
	else if(  Distance(wolf.GetPosition(),fox.GetPosition()) < 800 && rabbit.IsDeleted() == true)// fox trying to flee from wolf with the full stomach
	{
		steerFox = fox.flee(wolf.GetPosition(), foxSpeed);
		
	}
	
	if (Bush.IsDeleted() == true && Distance(wolf.GetPosition(), fox.GetPosition()) < 400)//fox wanders when bush is deleted
	{
		steerFox = fox.wander(foxWanderSpeed);

	}
	
	if (Distance(trap.GetPosition(), wolf.GetPosition()) < 120)// wolf running away from the trap

	{

		steerWolf = wolf.flee(trap.GetPosition(),wolfSpeed);
	}
	else if (Distance(trap1.GetPosition(), wolf.GetPosition()) < 120)// wolf running away from the trap

	{

		steerWolf = wolf.flee(trap1.GetPosition(), wolfSpeed);
	}
	else if (Distance(trap2.GetPosition(), wolf.GetPosition()) < 120)// wolf running away from the trap

	{

		steerWolf = wolf.flee(trap2.GetPosition(), wolfSpeed);

	}
	else if (Distance(trap3.GetPosition(), wolf.GetPosition()) < 120)// wolf running away from the trap

	{

		steerWolf = wolf.flee(trap3.GetPosition(), wolfSpeed);

	}


	// Calculate the Fox Steering Force
	

	if (IsGameOver())
	{
		
		if (GetTime() > 5000)
			NewGame();
		apple.UnDelete();
		rabbit.UnDelete();  // spawning sprites back after 5 seconds when the game is over
		carrot.UnDelete();
		Bush.UnDelete();



		return;
	}
	
	


	
	
	

	// Apply the Steering Forces
	fox.Accelerate(steerFox * (float)GetDeltaTime() / 1000.f);
	rabbit.Accelerate(steerRabbit * (float)GetDeltaTime() / 1000.f);
	apple.Accelerate(steerApple * (float)GetDeltaTime() / 1000.f);
	carrot.Accelerate(steerCarrot* (float)GetDeltaTime() / 1000.f);
	wolf.Accelerate(steerWolf * (float)GetDeltaTime() / 1000.f);

	// Rotate both animals so that are always heading their motion direction
	fox.SetRotation(fox.GetDirection());
	rabbit.SetRotation(rabbit.GetDirection());
	apple.SetRotation(apple.GetDirection());
	wolf.SetRotation(wolf.GetDirection());
	carrot.SetRotation(wolf.GetDirection());


	// update the rabbit and fox positions
	rabbit.Update(GetTime());
	fox.Update(GetTime());
	apple.Update(GetTime());
	wolf.Update(GetTime());
	carrot.Update(GetTime());
	rHouse.Update(GetTime());

	trap.Update(GetTime());
	trap1.Update(GetTime());
	trap2.Update(GetTime());
	trap3.Update(GetTime());

	fTrap.Update(GetTime());
	fTrap1.Update(GetTime());

	Bush.Update(GetTime());
	


	// keeping all sprites within the scene
	extern CGameApp app;
	rabbit.wrapToScreen(app.GetWidth(), app.GetHeight());
	fox.wrapToScreen(app.GetWidth(), app.GetHeight());
	apple.wrapToScreen(app.GetWidth(), app.GetHeight());
	wolf.wrapToScreen(app.GetWidth(), app.GetHeight());
	carrot.wrapToScreen(app.GetWidth(), app.GetHeight());
	rHouse.wrapToScreen(app.GetWidth(), app.GetHeight());

	trap.wrapToScreen(app.GetWidth(), app.GetHeight());
	trap1.wrapToScreen(app.GetWidth(), app.GetHeight());
	trap2.wrapToScreen(app.GetWidth(), app.GetHeight());
	trap3.wrapToScreen(app.GetWidth(), app.GetHeight());
	

	fTrap.wrapToScreen(app.GetWidth(), app.GetHeight());
	fTrap1.wrapToScreen(app.GetWidth(), app.GetHeight());

	Bush.wrapToScreen(app.GetWidth(), app.GetHeight());

	// hit test condition for the game over

	if (wolf.HitTest(&fox)&& rabbit.IsDeleted()==true)

		GameOver();

	
	
	
}

void CMyGame::OnDraw(CGraphics* g)
{
	// Draw the Background
	g->Blit(CVectorI(0, 0), grass);

	rabbit.Draw(g);
	fox.Draw(g);
	apple.Draw(g);
	wolf.Draw(g);
	carrot.Draw(g);
	rHouse.Draw(g);

    trap.Draw(g);
	trap1.Draw(g);
	trap2.Draw(g);
	trap3.Draw(g);

	fTrap.Draw(g);
	fTrap1.Draw(g);
	
	Bush.Draw(g);

		*g << font(40) << left << top << color(CColor::Red()) << "Score:  ";
	if (IsGameOver())
		*g << font(48) << center << vcenter << color(CColor::White()) << "OM NOM NOM NOM!" << endl << font(20) << "PRESS F2 TO RESTART";


}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{

	// Setting position and velocity of sprites
	apple.SetVelocity(0, 0);
    apple.SetRotation(0);
	apple.SetPosition(150, 400);

	rabbit.SetVelocity(0, 0);
	rabbit.SetRotation(0);
	rabbit.SetPosition(50, 550);

	fox.SetVelocity(0, 0);
	fox.SetRotation(0);
	fox.SetPosition(750, 50);


	wolf.SetVelocity(0, 0);
	wolf.SetRotation(1);
	wolf.SetPosition(350, 50);
	

	carrot.SetVelocity(0, 0);
	carrot.SetRotation(0);
	carrot.SetPosition(100, 250);

	rHouse.SetVelocity(0, 0);
	rHouse.SetRotation(0);
	rHouse.SetPosition(600, 500);

	trap.SetPosition(1200, 600);
	trap1.SetPosition(100, 60);
	trap2.SetPosition(1200, 50);
	trap3.SetPosition(100, 600);

	fTrap.SetPosition(1200, 300);
	fTrap1.SetPosition(100, 300);

	Bush.SetPosition(350, 50);

	StartGame();

}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
	

}

// called when Game is Over
void CMyGame::OnGameOver()
{

}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)   // when pressing f2 all sprites spawn back
	{
		rabbit.UnDelete();
		apple.UnDelete();
		carrot.UnDelete();
		Bush.UnDelete();
		NewGame();

	}
	
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
	if (!IsGameOver())
		rabbit.SetPosition(x, y); // player can only spawn mouse with left click btn
	   
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
