#include "ChuongTrinh.h"

Program::Program()
{
	FixConsoleWindow();
	FixSizeWindow(123, 200);
	this->Vol = nullptr;
}

Program::~Program()
{
	if (this->Vol != nullptr) {
		delete this->Vol;
		this->Vol = nullptr;
	}
}

void Program::run()
{
	this->homeNavigate();
}

void Program::openVolume()
{
	system("cls");

	while (true) {
		setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
		GUI::printTextAtMid("===== OPEN A VOLUME =====");
		cout << "\n\n";

		// Show list of recently opened volume paths in cache
		this->Cache.showListOfRecentlyOpenedVolume();
		cout << "\n";

		// Input
		if (this->Cache.isEmpty()) {
			cout << "  Program: * Input a path to open a volume" << "\n";
		}
		else {
			cout << "  Program: * Input a path to open a volume" << "\n\n";
			cout << "           * Input";
			setColor(COLOR::WHITE, COLOR::BLACK);
			cout << " <i> ";
			setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
			cout << "to open a recent volume (i is the index in the above list)" << "\n\n";
			cout << "           * Input";
			setColor(COLOR::WHITE, COLOR::BLACK);
			cout << " <clear cache> ";
			setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
			cout << "to clear the above list" << "\n\n";
		}

		cout << "           * Do not input anything then press Enter to";
		setColor(COLOR::YELLOW, COLOR::BLACK);
		cout << " EXIT";
		setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);

		cout << "\n\n" << "  User: ";

		setColor(COLOR::WHITE, COLOR::BLACK);
		string str;
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		getline(cin, str);

		// If the input is ""
		if (str == "") {
			return;
		}

		// If the input is "<clear cache>"
		if (str == "<clear cache>") {
			this->Cache.clear();
			system("cls");
			continue;
		}

		// If the input is <i>, change the content of str to the correspoding volume path
		bool openVolumeInCache = this->Cache.hasVolume(str);

		// Open this volume
		this->initializeVolume(str);

		if (this->Vol->isVolumeFile()) {
			this->Cache.add(this->Vol->getPath());
			this->Vol->open();
		}
		else {
			if (openVolumeInCache) {
				this->Cache.update();
			}

			setColor(COLOR::LIGHT_RED, COLOR::BLACK);
			cout << "\n";
			cout << "  Program: Cannot open this volume." << "\n\n";

			cout << "  ";
			system("pause");
		}

		this->closeVolume();
		break;
	}
}

void Program::createVolume()
{
	system("cls");

	setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
	GUI::printTextAtMid("===== CREATE A VOLUME =====");
	cout << "\n\n";

	// Input a path
	cout << "  Program: * Input a path to create a volume" << "\n\n";
	cout << "           * Do not input anything then press Enter to";
	setColor(COLOR::YELLOW, COLOR::BLACK);
	cout << " EXIT";
	setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
	cout << "\n\n" << "  User: ";

	setColor(COLOR::WHITE, COLOR::BLACK);
	string volumeFilePath;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	getline(cin, volumeFilePath);

	// If the input is ""
	if (volumeFilePath == "") {
		return;
	}

	// Create this volume
	this->initializeVolume(volumeFilePath + Volume::Extension);

	if (this->Vol->create()) {
		this->Cache.add(this->Vol->getPath());

		setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
		cout << "\n";
		cout << "  Program: * The new volume is created successfully!" << "\n\n";
		cout << "           * Press Enter to";
		setColor(COLOR::YELLOW, COLOR::BLACK);
		cout << " OPEN ";
		setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
		cout << "this volume" << "\n\n";
		cout << "           * Press any key except for Enter to";
		setColor(COLOR::YELLOW, COLOR::BLACK);
		cout << " EXIT";
		setColor(COLOR::LIGHT_CYAN, COLOR::BLACK);
		cout << "\n\n";

		while (true) {
			if (_kbhit()) {
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				if ((GetKeyState(VK_RETURN) & 0x8000)) {
					while ((GetKeyState(VK_RETURN) & 0x8000)) {};

					system("cls");
					this->Vol->open();
					break;
				}
				else {
					break;
				}
			}
		}
	}
	else {
		setColor(COLOR::LIGHT_RED, COLOR::BLACK);
		cout << endl;
		cout << "  Program: Cannot create a new volume." << "\n\n";
		cout << "           This path does not exist OR it is taken." << "\n\n";
		cout << "           Please input another path." << "\n\n";
		cout << "  ";
		system("pause");
	}

	this->closeVolume();
}

void Program::initializeVolume(string const& volumeFilePath)
{
	this->Vol = new Volume(volumeFilePath);
}

void Program::closeVolume()
{
	delete this->Vol;
	this->Vol = nullptr;
}

void Program::homeScreen() {
	setColor(5, 0);
	gotoXY(43, 11); cout << "       ##       ## ########";
	gotoXY(43, 12); cout << "       ###     ### ##      ";
	gotoXY(43, 13); cout << "       ####   #### ########";
	gotoXY(43, 14); cout << "       ## ## ##.## ##      ";
	gotoXY(43, 15); cout << "       ##  #### ## ##      ";
	gotoXY(43, 16); cout << "       ##  #### ## ##      ";
	gotoXY(43, 17); cout << "       ##       ## ##      ";

	setColor(5, 0);
	gotoXY(36, 23); cout << " .================================================." << endl;
	gotoXY(36, 24); cout << "||                                                ||" << endl;
	gotoXY(36, 25); cout << "||                                                ||" << endl;
	gotoXY(36, 26); cout << "||                                                ||" << endl;
	gotoXY(36, 27); cout << "||                                                ||" << endl;
	gotoXY(36, 28); cout << "||                                                ||" << endl;
	gotoXY(36, 29); cout << "||                                                ||" << endl;
	gotoXY(36, 30); cout << " *================================================*" << endl;

	setColor(14, 0);
	if (GUI::line == 0) setColor(15, 1);
	gotoXY(48, 25); cout << " 1.> Create a new volume     ";	setColor(15, 0);

	setColor(14, 0);
	if (GUI::line == 1) setColor(15, 1);
	gotoXY(48, 26); cout << " 2.> Open an volume "; setColor(15, 0);

	setColor(14, 0);
	if (GUI::line == 2) setColor(15, 1); 
	gotoXY(48, 27); cout << " 3.> Instruction             "; setColor(15, 0);

	setColor(14, 0);
	if (GUI::line == 3) setColor(15, 1);
	gotoXY(48, 28); cout << " 4.> Exit                    "; setColor(15, 0);
	//setColor(15, 0);
}

void Program::homeNavigate() {
	clrscr();
	GUI::clearBackground();

	bool back = false;

	this->homeScreen();

	GUI::line = 0;

	while (true) {

		if (_kbhit()) {
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

			// ============= ENTER =============
			if (GetKeyState(0x0D) & 0x8000) {
				while ((GetAsyncKeyState(VK_RETURN) & 0x8000)) {};

				clrscr();
				GUI::clearBackground();

				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

				switch (GUI::line) {
				case 0:
					this->createVolume();
					break;
				case 1:
					GUI::reset();
					this->openVolume();
					break;
				case 2:
					GUI::instructionScreen();
					break;
				case 3:
					back = true;
					break;
				}
				GUI::clearBackground();
				GUI::reset();

				GUI::esc = false;
			}

			// ============= UP =============
			if (GetKeyState(VK_UP) & 0x8000) {
				if (GUI::line == 0) {
					GUI::line = 3;
				}
				else GUI::line--;
				GUI::line %= 4;
			}

			// ============= DOWN =============
			if (GetKeyState(VK_DOWN) & 0x8000) {
				GUI::line++;
				GUI::line %= 4;
			}

			// ============= EXIT =============
			if (GetKeyState(0x1B) & 0x8000) {
				while ((GetAsyncKeyState(0x1B) & 0x8000)) {};

				back = true;
			}

			// Refresh 
			if (!GUI::esc) {
				clrscr();
				GUI::clearBackground();

				homeScreen();
			}

			if (back) {
				break;
			}
		}

	}
}
