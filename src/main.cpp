#include <appdef.h>
#include <sdk/os/debug.h>
#include <sdk/os/string.h>
#include <sdk/os/lcd.h>
#include <sdk/os/input.h>
#include <sdk/calc/calc.h>

APP_NAME("Physium Formulae")
APP_AUTHOR("SciMath-Solvers")
APP_DESCRIPTION("Physics Solver for HollyHock 3")
APP_VERSION("1.0.0")



void Print(int x, int y, const char* text, int *zero = nullptr){
	if(zero == nullptr && (x < 8) && (y < 12)) {
  	Debug_Printf(x,y,false,0,"%s", text);
  	LCD_Refresh();
	} else if( zero != nullptr) {
		Debug_Printf(x,y,false,0,"%s", text);
  	LCD_Refresh();
	} else {
		Debug_Printf(1,11,false,0,"%s", "Code ERROR");
		Debug_Printf(1,8,false,0,"%s", "Report Issue to:");
		Debug_Printf(1,9,false,0,"%s", "@PhysForm");
		LCD_Refresh();
	}
}

char* dtstr(double value, char* buffer, int precision = 1000000000) {
    // Basic implementation for positive numbers and limited precision
    long long intPart = static_cast<long long>(value);
    double fracPart = value - intPart;

    int i = 0;
    // Convert integer part
    if (intPart == 0) {
        buffer[i++] = '0';
    } else {
        // Reverse digits
        char temp[20]; // Temporary buffer for digits
        int k = 0;
        while (intPart > 0) {
            temp[k++] = (intPart % 10) + '0';
            intPart /= 10;
        }
        while (k > 0) {
            buffer[i++] = temp[--k];
        }
    }

    // Add decimal point and fractional part (simplified)
    if (precision > 0) {
        buffer[i++] = '.';
        for (int p = 0; p < precision; ++p) {
            fracPart *= 10;
            int digit = static_cast<int>(fracPart);
            buffer[i++] = digit + '0';
            fracPart -= digit;
        }
    }
    buffer[i] = '\0'; // Null-terminate the string
    return buffer;
}
void UPD(){
	LCD_Refresh();
}
int pow(double base, double exp) {
	int result = 1;
	for (int i = 0; i < exp; ++i) {
		result *= base;
	}
	return result;
}
int factorial(int n){
	if(n == 1){
		double result = 1;
		return result;
	} else{
		double result = 1;
		for(int i = 1; i <= n; i++){
			result *= i;
		}
		return result;
	}
}
int cos(double x,double termn = 1000000000000000000){
	int cos_x = 0;
	if(x < 45 and x > 0){
		return (1 - (0.000145 *(x * x)));
	}else{
		for (int n =0; n < termn; ++n) { //for (int n = 0; n < 10; ++n) {// Code to be executed in each iteration}
			double pow_x = 2*n;
			int term = ( pow((-1),n) * pow(x,pow_x)) / factorial(pow_x);
			cos_x += term;
		}
	}
	return cos_x;
}

double Input(){
  char num[13];
  int pos = 1;
  String_Strcpy(num, ">_                            ");

  struct Input_Event event;
  while (true) {
    Debug_Printf(1,43,false,0,"%s",num); UPD();
		GetInput(&event,0xFFFFFFFF,0x10);
    if(event.type==EVENT_KEY){
      if( event.data.key.direction==KEY_PRESSED){
        if(pos<=28){
          switch(event.data.key.keyCode){
            case KEYCODE_0: num[pos++]='0';num[pos]='_';break;
						case KEYCODE_1: num[pos++]='1';num[pos]='_';break;
						case KEYCODE_2: num[pos++]='2';num[pos]='_';break;
						case KEYCODE_3: num[pos++]='3';num[pos]='_';break;
						case KEYCODE_4: num[pos++]='4';num[pos]='_';break;
						case KEYCODE_5: num[pos++]='5';num[pos]='_';break;
						case KEYCODE_6: num[pos++]='6';num[pos]='_';break;
						case KEYCODE_7: num[pos++]='7';num[pos]='_';break;
						case KEYCODE_8: num[pos++]='8';num[pos]='_';break;
						case KEYCODE_9: num[pos++]='9';num[pos]='_';break;
            case KEYCODE_NEGATIVE: num[pos++]='-';num[pos]='_';break;
            case KEYCODE_EXP: Print(1,1,"No Exponents in Double Please");break;
						case KEYCODE_OPEN_PARENTHESIS:Print(1,1,"No Special Characters in Double Please");break;
            case KEYCODE_CLOSE_PARENTHESIS:Print(1,1,"No Special Characters in Double Please");break;
            case KEYCODE_PLUS:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_MINUS:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_EQUALS:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_TIMES:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_DIVIDE:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_COMMA:Print(1,1,"No Special Characters in Double Please");break;
            case KEYCODE_POWER: Print(1,1,"No Exponents in Double Please");break;
            case KEYCODE_BACKSPACE: 
              if(pos>1){
                num[pos--]=' ';num[pos]='_';break;
              } else{
                Print(1,1,"ERROR: TOO LITTLE \nCHARACTERS");
              }
            case KEYCODE_EXE: 
					    while(num[1]!='_' && num[1]!='.'){
						    double ret = num[1]-'0';
						    int i=2;
						    while(num[i]!='_'){
						    	ret = (ret*10) + (num[i]-'0');
						    	i++;
						    }//num[i]!='_'
						    return ret;
              			} 
							break;
            case KEYCODE_X: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_Y: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_Z: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_POWER_CLEAR: Print(1,1,"CLEAR NOT AVAILABLE USE: BACKSPACE");break;
            case KEYCODE_DOWN:   Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_UP:    Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_LEFT:    Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_RIGHT :   Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_DOT: 
							if (pos==1){
								if(num[1]=='.'){
                  return 0.0;
								}else{ 
									break;
									num[1]='.';
									return 0.0; //Return 0.0 if the user inputs a dot at the start.
								}
							}break;
						case KEYCODE_KEYBOARD: 
							UPD();
							Print(1,1,"ERROR! ");
							return 0;
						case KEYCODE_SHIFT: 
							return 0;
            
          }
        }
      }
    } else{
      return 0;
    }
    
  };
}

void cls(){
	LCD_ClearScreen();
	fillScreen(0xFFFF);
}


int main() {
    	fillScreen(0xFFFF);
  		UPD();
		Print(6,2,"Physium Formulae");
		Print(6,3,"ClassPad");
		UPD();
		while(true){
    		uint32_t key1, key2;    // First create variables
    		getKey(&key1, &key2); 
			cls();   // then read the keys
    		if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
    		    break;
    		}else if(testKey(key1,key2, KEY_CLEAR)){
				break;
			};
		}
		fillScreen(0xFFFF);
		UPD();
  		Print(1,1,"Physium Formulae\nClassPad");
		Print(6,1,"[1] Solver");
		Print(6,2,"[2] Formulas");
		Print(6,3,"[3] Exit");
		UPD();
		uint32_t Menukey, MenKey;
		getKey(&Menukey, &MenKey);
		cls();
		if(Menukey == KEY_1){
			fillScreen(0xFFFF);
			UPD();
      		Print(1,1,"Physium Formulae\nClassPad");
			uint32_t k1, k2;
			getKey(&k1, &k2);
			Print(1,3,"Main Solver Menu");
			Print(1,5,"[1] GPE  GPE = m*g*h");
			Print(1,6,"[2] Force F = m * a ");
			Print(1,8,"[3] Momentum = m * v");
			Print(1,9,"[4] Basic Work = F * d");
			Print(1,10,"[5] Work = F * d * cos(theta)"); 
			UPD();
			uint32_t SMenukey;
			uint32_t Skey;
			getKey(&SMenukey, &Skey);
			UPD();
			cls();
			if(SMenukey == KEY_1){
      	Print(1,1,"Physium Formulae\nClassPad");
				Print(6,3,"GPE Solver Submenu");
				Print(6,4,"[1] GPE",0);
				Print(6,5,"[2] Mass",0);
				Print(6,6,"[3] Acceleration to Gravity",0);
				Print(6,7,"[4] Height",0);
				UPD();
				uint32_t GPEKey;
				uint32_t ConfGPE;
				getKey(&GPEKey, &ConfGPE);
				UPD();
				cls();
				if(GPEKey == KEY_1){
					Print(1,1,"Mass?");
					UPD();
					double m = Input();
					cls();
					Print(1,1,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = Input();
					cls();
					Print(1,1,"Height?");
					UPD();
					double h = Input();
					double GPE = g*m*h;
					cls();
					char* GPEAns = nullptr;
					Print(1,1, "GPE = ");
					Print(1, 2, dtstr(GPE,GPEAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				}else if(GPEKey == KEY_2){
        			Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(1,1,"GPE=?");
					UPD();
					double GPE = Input();
        			cls();
    	    		Print(1,1,"Physium Formulae\nClassPad", 0);
	        		Print(1,3,"Acceleration to \nGravity g on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
    	    		UPD();
        			double g = Input();
        			cls();
        			Print(1,1,"Physium Formulae\nClassPad", 0);
        			Print(1,3,"Height=?");
        			UPD();
        			double h = Input();
        			cls();
	        		Print(1,1,"Physium Formulae\nClassPad", 0);
    	    		Print(160,264,"Mass =");
					double m = (GPE /(g*h));
					char* Mass = nullptr;
					Print(160,264,dtstr(m,Mass));
					UPD();
					while(true){
    	  				uint32_t key1, key2;    // First create variables
      					getKey(&key1, &key2);    // then read the keys
      					break;
	    			};
				}else if(GPEKey == KEY_3){
        			Print(1,1,"Physium Formulae\nClassPad", 0);
        			Print(160,264,"GPE = ?");
					UPD();
					double GPE = Input();
					cls();
        			Print(1,1,"Physium Formulae\nClassPad", 0);
        			Print(160,264,"Mass = ?");
					UPD();
					double Mass = Input();
					cls();
        			Print(1,1,"Physium Formulae\nClassPad", 0);
        			Print(160,264,"Height = ?");
					UPD();
					double Height = Input();
					cls();
					double g = GPE / (Mass * Height);
					char* gAns = nullptr;
					Print(160,264,"Acceleration to Gravity =");
					Print(160,298,dtstr(g,gAns));
					UPD();
					while(true){
    	  				uint32_t key1, key2;    // First create variables
      					getKey(&key1, &key2);    // then read the keys
						break;
	    			};
				}else if(GPEKey == KEY_4){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"GPE = ?");
					UPD();
					double GPE = Input();
					cls();
					Print(160,264,"Mass = ?");
					UPD();
					double Mass = Input();
					cls();
					Print(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = Input();
					cls();
					double Height = GPE / (Mass * g);
					char* HeightAns = nullptr;
					Print(160,264,"Height =");
					Print(160,298,dtstr(Height,HeightAns));
					UPD();
					while(true){
		  				uint32_t key1, key2;    // First create variables
	  					getKey(&key1, &key2);
						break; // Break the loop to exit the program
	    			};
				}
		
			} else if(SMenukey == KEY_2){
				Print(1,1,"Physium Formulae\nClassPad", 0);
				Print(1,3,"Force Solver Submenu",0);
				Print(1,4,"[1] Force",0);
				Print(1,5,"[2] Mass",0);
				Print(1,6,"[3] Acceleration",0);
				UPD();
				uint32_t ForceKey;
				uint32_t ConfForce;
				getKey(&ForceKey, &ConfForce);
				UPD();
				cls();
				if(ForceKey == KEY_1){
					Print(160,264,"Mass?");
					UPD();
					double m = Input();
					cls();
					Print(160,264,"Acceleration?");
					UPD();
					double a = Input();
					double F = m * a;
					cls();
					char* ForceAns = nullptr;
					Print(160,150,"Force = ");
					Print(160,264,dtstr(F,ForceAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				}else if(ForceKey == KEY_2){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Force=?");
					UPD();
					double F = Input();
					cls();
		    	Print(1,1,"Physium Formulae\nClassPad", 0);
	        Print(160,264,"Acceleration?");
		    	UPD();
					double a = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass =");
					double m = F / a;
					char* MassAns = nullptr;
					Print(160,264,dtstr(m,MassAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					};
				} else if(ForceKey == KEY_3){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Force = ?");
					UPD();
					double F = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass = ?");
					UPD();
					double m = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Acceleration =");
					double a = F / m;
					char* AccelAns = nullptr;
					Print(160,264,dtstr(a,AccelAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					};
				}
			} else if(SMenukey == KEY_3){
				Print(1,1,"Physium Formulae\nClassPad", 0);
				Print(160,264,"Momentum Solver Submenu");
				Print(160,264+17,"[1] Momentum");
				Print(160,264+17+17,"[2] Mass");
				Print(160,264+34+17,"[3] Velocity");
				UPD();
				uint32_t pKey, pkeyconf;
				getKey(&pKey, &pkeyconf);
				cls();
				if(pKey == KEY_1){
					Print(160,264,"Mass?");
					UPD();
					double m = Input();
					cls();
					Print(160,264,"Velocity?");
					UPD();
					double v = Input();
					double p = m * v;
					cls();
					char* pAns = nullptr;
					Print(160,150,"Momentum = ");
					Print(160,264,dtstr(p,pAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(pKey == KEY_2){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Momentum=?");
					UPD();
					double p = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Velocity?");
					UPD();
					double v = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass =");
					double m = p / v;
					char* MasspAns = nullptr;
					Print(160,264,dtstr(m,MasspAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(pKey == KEY_3){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Momentum = ?");
					UPD();
					double p = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass = ?");
					UPD();
					double m = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Velocity =");
					double v = p / m;
					char* VelAns = nullptr;
					Print(160,264,dtstr(v,VelAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}
			} else if(SMenukey == KEY_5){
				Print(1,1,"Physium Formulae\nClassPad", 0);
				Print(160,264,"Basic Work Solver Submenu");
				Print(160,264+17,"[1] Basic Work");
				Print(160,264+34+17,"[2] Force");
				Print(160,264+51+17,"[3] Distance");
				UPD();
				uint32_t WorkKey;
				uint32_t Confwork;
				getKey(&WorkKey, &Confwork);
				cls();
				if(WorkKey == KEY_1){
					Print(160,264,"Force?");
					UPD();
					double F = Input();
					cls();
					Print(160,264,"Distance?");
					UPD();
					double d = Input();
					double W = F * d;
					cls();
					char* WorkAns = nullptr;
					Print(160,150,"Basic Work = ");
					Print(160,264,dtstr(W,WorkAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);
						break;
					}
				} else if(WorkKey == KEY_2){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Work=?");
					UPD();
					double W = Input();
					cls();
	        		Print(160,264,"Distance=?");
		    		UPD();
					double d = Input();
					cls();
		    		Print(1,1,"Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Force =");
		    		double F = W / d;
					char* ForceAns = nullptr;
					Print(160,264,dtstr(F,ForceAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}else if(WorkKey == KEY_3){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Work = ?");
					UPD();
					double W = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Force = ?");
					UPD();
					double F = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Distance =");
					double d = W / F;
					char* DistAns = nullptr;
					Print(160,264,dtstr(d,DistAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}
			} else if(SMenukey == KEY_6){
				Print(1,1,"Physium Formulae\nClassPad", 0);
				Print(160,264,"Work Solver Submenu");
				Print(160,264+17,"[1] Work");
				Print(160,264+34+17,"[2] Force");
				Print(160,264+51+17,"[3] Distance");
				Print(160,264+68+17,"[4] Angle (in degrees)");
				UPD();
				uint32_t WorkKey;
				uint32_t Confwork;
				getKey(&WorkKey, &Confwork);
				cls();
				if(WorkKey == KEY_1){
					Print(160,264,"Force?");
					UPD();
					double F = Input();
					cls();
					Print(160,264,"Distance?");
					UPD();
					double d = Input();
					cls();
					Print(160,264,"Angle in degrees?");
					UPD();
					double angle = Input();
					double radian = angle * (3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989 / 180.0); // Convert degrees to radians
					double cosValue = cos(radian);
					double W = F * d * cosValue;
					cls();
					char* WorkAns = nullptr;
					Print(160,150,"Work = ");
					Print(160,264,dtstr(W,WorkAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(WorkKey == KEY_2){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Work=?");
					UPD();
					double W = Input();
					cls();
		    	Print(1,1,"Physium Formulae\nClassPad", 0);
	      	Print(160,264,"Distance=?");
		    	UPD();
					double d = Input();
					cls();
	        		Print(160,264,"Angle in degrees?");
		    		UPD();
					double theta = Input();
					double radian = theta * (3.14159265358979323846 / 180.0); // Convert degrees to radians
					double cosValue = cos(radian);
					cls();
		    	Print(1,1,"Physium Formulae\nClassPad", 0);
	    		Print(160,264,"Force =");
	    		double F = W / (d * cosValue);
					char* ForceAns = nullptr;
					Print(160,264,dtstr(F,ForceAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}else if(WorkKey == KEY_3){
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Work = ?");
					UPD();
					double W = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Force = ?");
					UPD();
					double F = Input();
					cls();
					Print(1,1,"Physium Formulae\nClassPad", 0);
					Print(160,264,"Distance =");
	        		Print(160,264+17,"Angle in degrees?");
		    		UPD();
					double d = W / F;
					double angle = Input();
					double radian = angle * (3.14159265358979323846 / 180.0); // Convert degrees to radians
					double cosValue = cos(radian);
					d /= cosValue;
					char* DistAns = nullptr;
					Print(160,264,dtstr(d,DistAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(WorkKey == KEY_4){
		    		Print(1,1,"Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Work = ?");
		    		UPD();
		    		double W = Input();
		    		cls();
		    		Print(1,1,"Physium Formulae\nClassPad", 0);
		    		Print(160,264,"Force = ?");
		    		UPD();
		    		double F = Input();
		    		cls();
		    		Print(1,1,"Physium Formulae\nClassPad", 0);
		    		Print(160,264,"Distance = ?");
		    		UPD();
		    		double d = Input();
		    		cls();
		    		Print(1,1,"Physium Formulae\nClassPad", 0);
		    		Print(160,264,"Angle in degrees =");
		    		UPD();
		    		double radian = cos(W / (F * d)); // Calculate the angle in radians
		    		double angle = radian * (180.0 / 3.14159265358979323846); // Convert radians to degrees
		    		char* AngleAns = nullptr;
		    		Print(160,264,dtstr(angle,AngleAns));
		    		UPD();
		    		while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;	
					}
				}
			} else if(SMenukey == KEY_3){
				Print(1,1,"Physium Formulae\nClassPad", 0);
				Print(1,1,"NEW IDEA COMING SOON!",0);
				UPD();
				while(true){
					uint32_t key1, key2;    // First create variables
					getKey(&key1, &key2);    // then read the keys
					break;
				}
			}
		}else if (Menukey == KEY_2){
			cls();
    		Print(1,1,"Physium Formulae\nClassPad", 0);
			Print(1,1,"Formulas",0);
			Print(0,527,"WIP");
			Print(160,40,"GPE = mass * accel. to grav. * height");
			Print(160,80,"F = Mass * Acceleration");
			Print(160,120,"p = Mass * Velocity");
			Print(160,160,"Basic Work = Force * Distance");
			UPD();
			while(true){
				uint32_t key1, key2;    // First create variables
	  			getKey(&key1, &key2);
				break;
			};
		}else if (Menukey == KEY_3){
    		Print(1,1,"Physium Formulae\nClassPad", 0);
    		Print(1,3,"Program Terminating...",0);
    		UPD();
			while(true){
				cls();
				break;
			}
		}
		UPD();
		cls();
  Debug_WaitKey();
  return 0;
}
