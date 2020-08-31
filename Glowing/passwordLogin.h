#include <iostream>

bool verified = false;

void login() {

	string passwordAttempt;
	string password = "justVibingNGL";
	std::cout << "Password:";
	std::cin >> passwordAttempt;

	if (passwordAttempt != password) {
		for (int i = 0; i < 5; i++) {
			std::cout << "...\n";
			Sleep(100);
		}
		std::cout << "Access Denied!";
	}
	else {
		for (int i = 0; i < 5; i++) {
			std::cout << "...\n";
			Sleep(100);
		}
		std::cout << "Hack Initiated";
		verified = true;
	}
}
