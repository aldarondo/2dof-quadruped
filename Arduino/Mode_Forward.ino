
void modeForward()
{
	setTargetPosition(LEG_RIGHT_BACK_KNEE, LEG_RIGHT_BACK_KNEE_UP); 
	setTargetPosition(LEG_RIGHT_FRONT_HIP, LEG_RIGHT_FRONT_HIP_BACK); 
	moveToTarget(1);
	
	setTargetPosition(LEG_LEFT_BACK_KNEE, LEG_LEFT_BACK_KNEE_DOWN); 
	setTargetPosition(LEG_LEFT_BACK_HIP, LEG_LEFT_BACK_HIP_BACK);
	setTargetPosition(LEG_RIGHT_BACK_HIP, LEG_RIGHT_BACK_HIP_FORWARD);
	moveToTarget(2);  
	
	setTargetPosition(LEG_RIGHT_BACK_KNEE, LEG_RIGHT_BACK_KNEE_DOWN); 
	setTargetPosition(LEG_LEFT_FRONT_HIP, ANGLE_MIDDLE);
	moveToTarget(1); 

	setTargetPosition(LEG_RIGHT_FRONT_KNEE, LEG_RIGHT_FRONT_KNEE_UP); 
	setTargetPosition(LEG_RIGHT_FRONT_HIP, ANGLE_MIDDLE); 
	moveToTarget(1);

	setTargetPosition(LEG_RIGHT_FRONT_HIP, LEG_RIGHT_FRONT_HIP_FORWARD); 
	moveToTarget(1);
	
	setTargetPosition(LEG_RIGHT_FRONT_KNEE, LEG_RIGHT_FRONT_KNEE_DOWN); 
	setTargetPosition(LEG_RIGHT_BACK_HIP, LEG_RIGHT_BACK_HIP_BACK); 
	setTargetPosition(LEG_LEFT_FRONT_HIP, LEG_LEFT_FRONT_HIP_BACK);
	moveToTarget(1);
	
	setTargetPosition(LEG_LEFT_BACK_KNEE, LEG_LEFT_BACK_KNEE_UP);  
	moveToTarget(1); 

	setTargetPosition(LEG_LEFT_BACK_HIP, ANGLE_MIDDLE); 
	setTargetPosition(LEG_RIGHT_FRONT_HIP, ANGLE_MIDDLE); 
	moveToTarget(2);
	
	setTargetPosition(LEG_LEFT_BACK_KNEE, LEG_LEFT_BACK_KNEE_DOWN); 
	setTargetPosition(LEG_LEFT_BACK_HIP, LEG_LEFT_BACK_HIP_FORWARD); 
	moveToTarget(1);

	setTargetPosition(LEG_LEFT_FRONT_KNEE, LEG_LEFT_FRONT_KNEE_UP);
	setTargetPosition(LEG_RIGHT_BACK_HIP, LEG_RIGHT_BACK_HIP_BACK); 
	moveToTarget(1); 

	setTargetPosition(LEG_LEFT_FRONT_HIP, LEG_LEFT_FRONT_HIP_FORWARD);
	moveToTarget(1);

	setTargetPosition(LEG_LEFT_FRONT_KNEE, LEG_LEFT_FRONT_KNEE_DOWN);
	moveToTarget(1);

	delay(DELAY_STEP);
}