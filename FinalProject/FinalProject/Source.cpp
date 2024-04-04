/*
Author: Ryan Burchette
Date: 11/30/2022
Purpose: Blackjack Game
Class: CSC150; Prof. Caudill
*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <string>
using namespace std;

//function to check if user wants instructions and display it
void displayInstructions(bool newInstructScreen) {
	char instructChoice;
	string tempChoice;
	newInstructScreen = true;
	while (newInstructScreen = true) {
		cout << "\nWould you like to know the house rules? (Y/N): ";
		cin >> instructChoice;
		cout << endl;
		//if user wants instructions
		if (instructChoice == 'Y' || instructChoice == 'y') {
			Sleep(500);
			cout << "House Rules of Blackjack\n1.Your goal is to beat the dealer by getting as close to 21 as possible without going over.\n2.If the dealers face up card is an Ace(11) you can pay insurance for safety.\n     -Pay 1/2 the intial bet. If dealer has blackjack, you get all your money back. If they dont you lose the side bet.\n3.After your 2 intial cards you can either hit, stand, or double.\n     -hit: get another card (up to 5 cards total).\n     -stand: keep the cards you are at.\n     -double: double your bet, but you can only recieve 1 more card(can only do this as your first action).\n4.Whenever you stand, the dealer will flip their hidden card and continue hitting until they have 17+ or busts.\n5.Cards are compared and whoever has closest to 21 wins.\n6.If you reach 5 cards while <=21 you automatically win.\n7.If you get 21 on your first 2 cards you automatically win.\n8.Aces only count as 11.\n9.Payout is 3:2." << endl;
			Sleep(3500);
			cout << "\nType 'CONT' when you are ready to continue! : ";
			cin >> tempChoice;
			newInstructScreen = false;
			break;
		}
		//if user doesn't want instructions
		else if (instructChoice == 'n' || instructChoice == 'N') {
			newInstructScreen = false;
			break;
		}
		//if user inputted invalid answer
		else {
			cout << "\nInvalid input. Please try again" << endl;
			continue;
		}
	}
}

//checking if user bought insurance, if yes subtract from total
int insuranceLosses(bool insuranceBuy, int totalChips, int chipBet) {
	//if user bought insurance, increase removal of chips
	if (insuranceBuy == true) {
		totalChips -= (chipBet / 2);
	}
	return totalChips;
}

int main() {

	//declare variables
	int chipTotal = 1000;
	int userBet;
	int arrUserCards [5] = {0,0,0,0,0};
	int arrDealerCards [5] = {0,0,0,0,0};
	int runningUserTotal;
	int runningDealerTotal;
	int handCount = 1;
	string userName;
	char playChoice, hitStand, insuranceCheck;
	bool keepPlaying = true, instructScreen = true;
	bool insurance = false;
	
	//get users name
	cout << "Please enter your User Name: ";
	getline(cin, userName);

	//check if user wants to play blackjack
	cout << "\nDealer: Would you like to play some Blackjack " << userName << "? (Y/N) : ";
	cin >> playChoice;
	Sleep(500);

	//branch if they want to play
	if (playChoice == 'Y' || playChoice == 'y') {

		//check if user wants to see instructions
		displayInstructions(instructScreen);

		cout << "Dealer: Okay let us begin! You will start with $1000 and you lose when you run out of money!" << endl;
		Sleep(2000);

		//loop to play blackjack until users quit or runs out of money
		do{
			//creates rand seed
			srand(time(0));
			
			//resets usercard/dealercard array and running user total/running dealer total for next hand
			for (int j = 0; j < 5; j++) {
				arrUserCards[j] = 0;
			}
			runningUserTotal = 0;
			for (int j = 0; j < 5; j++) {
				arrDealerCards[j] = 0;
			}
			runningDealerTotal = 0;

			//gets bet amount
			cout << "\nThis is hand #" << handCount <<", how much money would you like to bet on this hand? : ";
			cin >> userBet;

			//validates that user bet is legal
			if (userBet > 0 && userBet <= chipTotal) {
				Sleep(1000);
				cout << "\nDealer: Alright here comes the cards!" << endl;
				Sleep(500);

				//generates user and dealer first 2 cards
				arrUserCards[0] = rand() % (10) + 2;
				arrUserCards[1] = rand() % (10) + 2;
				arrDealerCards[0] = rand() % (10) + 2;
				arrDealerCards[1] = rand() % (10) + 2;

				//since aces only equal 11, need to redraw cards at double 11's or else user automatically busts
				if (arrUserCards[0] == 11 && arrUserCards[1] == 11) {
					arrUserCards[0] = rand() % (10) + 2;
					arrUserCards[1] = rand() % (10) + 2;
				}
				if (arrDealerCards[0] == 11 && arrDealerCards[1] == 11) {
					arrDealerCards[0] = rand() % (10) + 2;
					arrDealerCards[1] = rand() % (10) + 2;
				}

				//calculates the intial running total
				runningUserTotal = arrUserCards[0] + arrUserCards[1];
				runningDealerTotal = arrDealerCards[0] + arrDealerCards[1];

				//displays user and dealer first 2 cards 
				Sleep(500);
				cout << "\nDealer: Your first two cards are: \n |" << arrUserCards[0] << "| |" << arrUserCards[1] << "|" << endl;
				Sleep(1500);
				cout << "\nDealer: Dealers first two cards are: \n |?| |" << arrDealerCards[1] << "|";
				cout << endl;
				Sleep(1500);


				//checks if user has blackjack
				if (runningUserTotal == 21) {
					cout << "\nBLACKJACK! Congrats you automatically win! Lets see if your luck continues " << userName  << "." << endl;
					chipTotal += (userBet * 1.5);
					Sleep(1000);
				}

				else {
					//loop to continue getting user card till bust or stands
					for (int i = 2; i <= 4; i++) {

						//checks if user wants insurance at the start if dealers face up card is 11
						if (arrUserCards[2] == 0 && arrDealerCards[1] == 11) {
							cout << "\nThe dealer has an ace, do you want insurance? (Y/N) : ";
							cin >> insuranceCheck;
							cout << endl;
							Sleep(500);
							//if user wants insurance
							if (insuranceCheck == 'Y' || insuranceCheck == 'y') {
								cout << "Okay, the insurance side bet has been placed" << endl;
								insurance = true;
							}
							//if user does not want insurance
							else if (insuranceCheck == 'N' || insuranceCheck == 'n') {
								cout << "Okay, no insurance side bet has been placed";
								insurance = false;
							}
							//if user inputted invalid option
							else {
								while (insuranceCheck != 'Y' && insuranceCheck != 'y' && insuranceCheck != 'N' && insuranceCheck != 'n') {
									cout << "Invalid option, please try again" << endl;
									Sleep(500);
									cout << "\nThe dealer has an ace, do you want insurance? (Y/N) : ";
									cin >> insuranceCheck;
									cout << endl;
									Sleep(500);
									if (insuranceCheck == 'Y' || insuranceCheck == 'y') {
										insurance = true;
										cout << "Okay, the insurance side bet has been placed" << endl;
										break;
									}
									else if (playChoice == 'N' || playChoice == 'n') {
										insurance = false;
										cout << "Okay, no insurance side bet has been placed";
										break;
									}
									else {
										continue;
									}
								}
							}
						}
						Sleep(1000);

						//checks what user would like to do next
						//displays only during users first choice
						if (arrUserCards[2] == 0) {
							cout << "\nWould you like to hit,stand or double? (H/S/D) :  ";
							Sleep(500);
							cin >> hitStand;
							cout << endl;
						}
						//displays if user hit any turn before
						else {
							cout << "\nWould you like to hit or stand? (H/S) :  ";
							Sleep(500);
							cin >> hitStand;
							cout << endl;
						}

						//validates user input
						while (hitStand != 'H' && hitStand != 'h' && hitStand != 'S' && hitStand != 's' && hitStand != 'D' && hitStand != 'd') {
							cout << "Invalid option, please try again" << endl;
							Sleep(500);
							cout << "\nWould you like to hit,stand or double? (H/S/D) : ";
							cout << endl;
							Sleep(500);
							cin >> hitStand;
							if (hitStand == 'H' || hitStand == 'h' || hitStand == 'S' || hitStand == 's' || hitStand == 'D' || hitStand == 'd') {
								break;
							}
							else {
								continue;
							}
						}

						//if user wants another card
						if (hitStand == 'H' || hitStand == 'h') {
							arrUserCards[i] = rand() % (10) + 2;
							runningUserTotal += arrUserCards[i];
							cout << "Your next card is |" << arrUserCards[i] << "|";
							Sleep(500);
							cout << " --- Which amounts to a new total of |" << runningUserTotal << "|" << endl;
							Sleep(1500);

							//checks if user busts after drawing card
							if (runningUserTotal > 21) {
								cout << "\nDealer: Darn that means you busted. Good luck in your future hands " << userName << "!" << endl;
								Sleep(1500);
								chipTotal -= userBet;
								chipTotal = insuranceLosses(insurance, chipTotal, userBet);
								break;
							}

							//checks if user pulled 5 cards while staying below 21
							else if (arrUserCards[4] > 0) {
								cout << "\nDealer: Congrats you hit the 5 card charlie! You automatically win!. Good luck in your future hands " << userName << "!" << endl;
								Sleep(1500);
								chipTotal += (userBet * 1.5);
								chipTotal = insuranceLosses(insurance, chipTotal, userBet);
								break;
							}

							continue;
						}

						//if user does not want another card or doubles
						else if (hitStand == 'S' || hitStand == 's' || hitStand == 'D' || hitStand == 'd') {

							//checks if user can double if selected
							if (arrUserCards[2] == 0  && (hitStand == 'D' || hitStand == 'd')) {
								//if user has enough money to double
								if ((chipTotal - (userBet * 2)) >= 0) {
									userBet *= 2;
									arrUserCards[2] = rand() % (10) + 2;
									runningUserTotal += arrUserCards[2];
									cout << "Your next card is |" << arrUserCards[i] << "|";
									Sleep(500);
									cout << " --- Which amounts to a new total of |" << runningUserTotal << "|" << endl;
									Sleep(1500);
									//checks if user busts after drawing card
									if (runningUserTotal > 21) {
										cout << "\nDealer: Darn that means you busted. Good luck in your future hands " << userName << "!" << endl;
										Sleep(1500);
										chipTotal -= userBet;
										chipTotal = insuranceLosses(insurance, chipTotal, userBet);
										break;
									}
								}
								//if user doesnt have enough money to double
								else {
									Sleep(500);
									cout << "Sorry " << userName << " but you don't have enough money to double!" << endl;
									Sleep(1500);
									continue;
								}
							}

							//if user tries to double on turn other than the first
							else if (arrUserCards[2] != 0 && (hitStand == 'D' || hitStand == 'd')) {
								cout << "Sorry " << userName <<  " but you can only double as your first action and since you hit first, you can only hit or stand!" << endl;
								Sleep(1500);
								continue;
							}

							//displays all cards that were drawn and user final total
							cout << "Dealer: Okay your final hand is ";
							for (int j = 0; j < 5; j++) {
								if (arrUserCards[j] != 0) {
									cout << "|" << arrUserCards[j] << "| ";
								}
							}
							Sleep(500);
							cout << "--- Which amounts to a total of |" << runningUserTotal << "|" << endl;
							Sleep(1500);
							cout << "\nDealer: The dealers current hand is \n|" << arrDealerCards[0] << "| |" << arrDealerCards[1] << "|" << endl;
							Sleep(1500);

							//loop to draw dealers cards
							for (int j = 2; j < 5; j++) {

								//checks if dealer should keep drawing
								if (runningDealerTotal < 17) {
									arrDealerCards[j] = rand() % (10) + 2;
									cout << "\nDealer: Dealers next card is |" << arrDealerCards[j] << "|";
									runningDealerTotal += arrDealerCards[j];
									Sleep(500);
									cout << " --- Which amounts to a new total of |" << runningDealerTotal << "|" << endl;
									Sleep(2000);

									//checks if dealer busted
									if (runningDealerTotal > 21) {
										cout << "\nDealer: Shoot looks like dealer busts. You win this hand " << userName << endl;
										Sleep(1500);
										chipTotal += (userBet * 1.5);
										chipTotal = insuranceLosses(insurance, chipTotal, userBet);
										break;
									}
								}
								else {
									break;
								}
							}

							//clumsily leaving loop if dealer busts since break only leaves one loop.
							if (runningDealerTotal > 21) {
								break;
							}

							//if dealer got blackjack
							if (arrDealerCards[2] == 0 && runningUserTotal == 21 && runningUserTotal != 21) {
								//if user bought insurance
								if (insurance) {
									cout << "\nDealer: Luckily you bought insurance, so you get your money back " << userName << "!" << endl;
								}
								//if user didn't buy insurance
								else {
									cout << "\nDealer: Looks like dealer won this hand. Good luck with your future hands " << userName << endl;
									chipTotal -= userBet;
								}
							}
							//result if users total is less than dealers
							else if (runningUserTotal < runningDealerTotal) {
								cout << "\nDealer: Looks like dealer won this hand. Good luck with your future hands " << userName << endl;
								//checking if user purchased insurance and removing chips if yes
								chipTotal -= userBet;
								chipTotal = insuranceLosses(insurance, chipTotal, userBet);
							}

							//result if users total is greater than dealers
							else if (runningUserTotal > runningDealerTotal) {
								cout << "\nDealer: Congrats looks like you won this hand. Good luck with your future hands " << userName << endl;
								chipTotal += (userBet * 1.5);
								//checking if user purchased insurance and removing chips if yes
								chipTotal = insuranceLosses(insurance, chipTotal, userBet);
							}

							//result if user tied with dealer
							else if (runningUserTotal == runningDealerTotal) {
								cout << "\nDealer: Well shoot it seems like we drew. Good luck with your future hands " << userName << endl;
								//checking if user purchased insurance and removing chips if yes
								chipTotal = insuranceLosses(insurance, chipTotal, userBet);
							}
							Sleep(1500);
							break;
						}


					}
				}
				
				//updates user on chip amount
				cout << "\nDealer: Your total chip amount is now " << chipTotal << "!" << endl;
				Sleep(1500);

				//if user runs out of money
				if (chipTotal == 0) {
					cout << "\nDealer: Darn looks like you are out of money! Should have played it safer!" << endl;
					Sleep(500);
					keepPlaying = false;
					break;
				}

				//checking if user wants to keep playing
				cout << "\nWould you like to play again? (Y/N): ";
				cin >> playChoice;

				//validating users input
				if (playChoice == 'Y' || playChoice == 'y') {
					keepPlaying = true;
					handCount++;
					Sleep(500);
				}
				else if(playChoice == 'N' || playChoice == 'n'){
					keepPlaying = false;
				}

				//if user inputted invalid input, loops until user gives valid input
				else {
					while (playChoice != 'Y' && playChoice != 'y' && playChoice != 'N' && playChoice != 'n') {
						cout << "Invalid option, please try again" << endl;
						Sleep(500);
						cout << "\nWould you like to play again? (Y/N): ";
						cin >> playChoice;
						cout << endl;
						Sleep(500);
						//if user wants to play again
						if (playChoice == 'Y' || playChoice == 'y') {
							keepPlaying = true;
							handCount++;
							break;
						}
						//if user does not want to play again
						else if (playChoice == 'N' || playChoice == 'n') {
							keepPlaying = false;
							break;
						}
						//if user put in invalid option again
						else {
							continue;
						}
					}
				}
			}

			//if bet amount invalid
			else {
				cout << "\nInvalid Bet Amount. Insufficient Funds! You have " << chipTotal << " in your account" << endl;
				continue;
			}

			
		} while (keepPlaying == true);

		//Message for whenever user wants to quit playing and played one hand
		Sleep(500);
		if (handCount == 1) {
			cout << "\nYou played " << handCount << " hand and ended with " << chipTotal << " worth of chips. Thanks for playing " << userName << "!" << endl;
		}
		//Message for whenever user wants to quit playing and played more than one hand
		else {
			cout << "\nYou played " << handCount << " hands and ended with " << chipTotal << " worth of chips. Thanks for playing " << userName << "!" << endl;
		}
		Sleep(1500);
	}

	//branch if the user does not want to play
	else {
		cout << "\nOh, sorry didn't mean to bother you. Carry on with your day then." << endl;
	}
}