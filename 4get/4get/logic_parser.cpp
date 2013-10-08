#include "logic_parser.h"


Parser::Parser()
{
	textInput = INITIALIZE_STRING_BLANK;
	_textInput = INITIALIZE_STRING_BLANK;
	textCommand = INITIALIZE_STRING_BLANK;
	textDescription = INITIALIZE_STRING_BLANK;
	textVenue = INITIALIZE_STRING_BLANK;
	textDateAndTime = INITIALIZE_STRING_BLANK;
	textRepeat = INITIALIZE_STRING_BLANK;
	textPriority = INITIALIZE_STRING_BLANK;
	textRemindDateAndTime = INITIALIZE_STRING_BLANK;
	textSlotNumber = INITIALIZE_STRING_BLANK;
	textTaskList = INITIALIZE_STRING_BLANK;
}


void Parser::processCommand(string commandString, vector<string>& inputBits)
{
	try{
		if(commandString.compare(COMMAND_A)==COMPARE_SUCCESS || commandString.compare(COMMAND_ADD)==COMPARE_SUCCESS || commandString.compare(COMMAND_NEW_TASK)==COMPARE_SUCCESS){
			inputBits[SLOT_COMMAND] = COMMAND_ADD;
			if(!separateInput(commandAdd, inputBits)){
				throw MESSAGE_ERROR_COMMAND_ADD;
			}
		}
		else if(commandString.compare(COMMAND_DEL)==COMPARE_SUCCESS || commandString.compare(COMMAND_DELETE)==COMPARE_SUCCESS || commandString.compare(COMMAND_ERASE)==COMPARE_SUCCESS ||commandString.compare(COMMAND_REM)==COMPARE_SUCCESS || commandString.compare(COMMAND_REMOVE)==COMPARE_SUCCESS) {
			inputBits[SLOT_COMMAND] = COMMAND_DELETE;
			if(!separateInput(commandDelete, inputBits)){
				throw MESSAGE_ERROR_COMMAND_DELETE;
			}
		}
		else if(commandString.compare(COMMAND_DEL_ALL)==COMPARE_SUCCESS || commandString.compare(COMMAND_DELETE_ALL)==COMPARE_SUCCESS || commandString.compare(COMMAND_ERASE_ALL)==COMPARE_SUCCESS ||commandString.compare(COMMAND_REM_ALL)==COMPARE_SUCCESS || commandString.compare(COMMAND_REMOVE_ALL)==COMPARE_SUCCESS) {
			inputBits[SLOT_COMMAND] = COMMAND_DELETE_ALL;
			if(!separateInput(commandDeleteAll, inputBits)){
				throw MESSAGE_ERROR_COMMAND_DELETE;
			}
		}
		else if(commandString.compare(COMMAND_M)==COMPARE_SUCCESS || commandString.compare(COMMAND_MARK)==COMPARE_SUCCESS) {
			inputBits[SLOT_COMMAND] = COMMAND_MARK;
			if(!separateInput(commandMark, inputBits)){
				throw MESSAGE_ERROR_COMMAND_MARK;
			}
		}
		else if(commandString.compare(COMMAND_M_DONE)==COMPARE_SUCCESS || commandString.compare(COMMAND_MARK_DONE)==COMPARE_SUCCESS) {
			inputBits[SLOT_COMMAND] = COMMAND_MARK;
			if(!separateInput(commandMarkDone, inputBits)){
				throw MESSAGE_ERROR_COMMAND_MARK;
			}
		}
		else if(commandString.compare(COMMAND_MOD)==COMPARE_SUCCESS || commandString.compare(COMMAND_MODIFY)==COMPARE_SUCCESS) {
			inputBits[SLOT_COMMAND] = COMMAND_MODIFY;
			if(!separateInput(commandModify, inputBits)){
				throw MESSAGE_ERROR_COMMAND_MODIFY;
			}
		}
		else if(commandString.compare(COMMAND_UNDO)==COMPARE_SUCCESS) {
			inputBits[SLOT_COMMAND] = COMMAND_UNDO;
			if(!separateInput(commandUndo, inputBits)){
				throw MESSAGE_ERROR_COMMAND_UNDO;
			}
		}
		else if(commandString.compare(COMMAND_UPDATE)==COMPARE_SUCCESS) {
			inputBits[SLOT_COMMAND] = COMMAND_UPDATE;
			if(!separateInput(commandUpdate, inputBits)){
				throw MESSAGE_ERROR_COMMAND_UPDATE;
			}
		}
	}
	catch(string error)
	{
		cout << error << endl;
	}

}

void Parser::parseInput(string input, vector<string>& inputBits)
{
	removeFirstWord(input);
	_textInput = textInput = input;
	toLowerCase(textInput);

	processCommand(textCommand, inputBits);
	populateContainer(inputBits);

}


bool Parser::separateInput(Command userCommand, vector<string>& inputBits)
{

	switch (userCommand){
	case commandAdd: 
		return separateFunctionAdd(inputBits);
	case commandDelete:
		return separateFunctionDelete(inputBits);
	case commandDeleteAll:
		return separateFunctionDeleteAll(inputBits);
	case commandMark:
		return separateFunctionMark(inputBits);
	case commandMarkDone:
		return separateFunctionMarkDone(inputBits);
	case commandModify:
		return separateFunctionModify(inputBits);
	case commandUndo:
		return separateFunctionUndo(inputBits);
	case commandUpdate:
		return separateFunctionUpdate(inputBits);
	default:
		return false;
	}



}

bool Parser::separateFunctionAdd(vector<string>& inputBits)
{

	if(!determineVenue())
		return false;

	if(!determineDateAndTime())
		return false;

	if(!determineRepeat())
		return false;

	if(!determinePriority())
		return false;

	if(!determineReminder())
		return false;

	textDescription = _textInput;
	cout << "command: <" << textCommand << ">" << endl;
	cout << "description: <" << textDescription << ">" << endl;
	cout << "venue: <" << textVenue << ">" << endl;
	cout << "D&T: <" << textDateAndTime << ">" << endl;
	cout << "repeat: <" << textRepeat << ">" << endl;
	cout << "priority: <" << textPriority << ">" << endl;
	cout << "reminder: <" << textRemindDateAndTime << ">" << endl;

	return true;
}
bool Parser::separateFunctionDelete(vector<string>& inputBits)
{
	if(!determineTaskList())
		return false;
	if(!determineSlot())
		return false;

	cout << "slot number: <" << textSlotNumber << ">" << endl;
	cout << "TaskList: <" << textTaskList <<  ">" << endl;

	return true;
}
bool Parser::separateFunctionDeleteAll(vector<string>& inputBits)
{

	return true;
}
bool Parser::separateFunctionMark(vector<string>& inputBits)
{
	return true;
}
bool Parser::separateFunctionMarkDone(vector<string>& inputBits)
{
	return true;
}

bool Parser::separateFunctionModify(vector<string>& inputBits)
{
	return true;
}

bool Parser::separateFunctionUndo(vector<string>& inputBits)
{
	return true;
}
bool Parser::separateFunctionUpdate(vector<string>& inputBits)
{
	return true;
}

bool Parser::determineVenue()
{
	std::size_t found = 0;
	std::size_t foundComma = 0;
	std::size_t extractStartPos;
	std::size_t extractLength;
	std::size_t stringLength = textInput.size();
	std::size_t i;
	string marker = INITIALIZE_STRING_BLANK;

	if(textInput.find(MARKER_AT)!=std::string::npos){
		found = textInput.find(MARKER_AT);
		if(textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_AT_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_AT, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY){
				textVenue = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else if(textInput.find(MARKER_NEAR)!=std::string::npos){
		found = textInput.find(MARKER_NEAR);
		if(textInput.find(MARKER_COMMA, found+MARKER_NEAR_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_NEAR_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_NEAR, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY){
				textVenue = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else

				return false;
		}
		else
			return false;
	}
	else
		return false; 
}

bool Parser::determineDateAndTime()
{
	std::size_t found = 0;
	std::size_t foundComma = 0;
	std::size_t extractStartPos;
	std::size_t extractLength;
	std::size_t stringLength = textInput.size();
	std::size_t i;
	string marker = INITIALIZE_STRING_BLANK;


	if(textInput.find(MARKER_BY)!=std::string::npos){
		found = textInput.find(MARKER_BY);
		if(textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH)!=std::string::npos ){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_BY_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_BY, extractStartPos);
			i = foundComma; 
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY){
				textDateAndTime = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else if(textInput.find(MARKER_FROM)!=std::string::npos){
		found = textInput.find(MARKER_FROM);
		if(textInput.find(MARKER_COMMA, found+MARKER_FROM_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_FROM_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_FROM, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if((marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_REPEAT || marker==MARKER_PRIORITY) && textInput.find(MARKER_TO, found)!=std::string::npos){
				textDateAndTime = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false; 
}

bool Parser::determineRepeat()
{
	std::size_t found = 0;
	std::size_t foundComma = 0;
	std::size_t extractStartPos;
	std::size_t extractLength;
	std::size_t stringLength = textInput.size();
	std::size_t i;
	string marker = INITIALIZE_STRING_BLANK;


	if(textInput.find(MARKER_REPEAT)!=std::string::npos){
		found = textInput.find(MARKER_REPEAT);
		if(textInput.find(MARKER_COMMA, found+MARKER_REPEAT_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_REPEAT_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_REPEAT, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REMIND || marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_PRIORITY){
				textRepeat = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	else
		return false; 
}

bool Parser::determinePriority()
{
	std::size_t found = 0;
	std::size_t foundEnclose;
	std::size_t extractStartPos;
	std::size_t extractLength;

	if(textInput.rfind(MARKER_PRIORITY)!=std::string::npos){
		found = textInput.find(MARKER_PRIORITY);
		if(textInput.find(MARKER_ENCLOSE, found+MARKER_PRIORITY_LENGTH)!=std::string::npos){
			foundEnclose = textInput.find(MARKER_ENCLOSE, found+MARKER_PRIORITY_LENGTH);
			extractLength = determindExtractLength(found, foundEnclose, MARKER_PRIORITY, extractStartPos);
			textPriority = _textInput.substr(extractStartPos, extractLength);
			shortenInput(found, foundEnclose);
			return true;
		}

		else{
			extractStartPos = found;
			textPriority = _textInput.substr(++extractStartPos);
			shortenInput(found, MARKER_PRIORITY_LENGTH);
			return true;
		}
	}

	else 
		return false;

}

//reminder is not neccessary. If user defines Reminder in input, then it will process.
bool Parser::determineReminder()
{
	std::size_t found = 0;
	std::size_t foundComma = 0;
	std::size_t extractStartPos;
	std::size_t extractLength;
	std::size_t stringLength = textInput.size();
	std::size_t i;
	string marker = INITIALIZE_STRING_BLANK;


	if(textInput.find(MARKER_REMIND)!=std::string::npos){
		found = textInput.find(MARKER_REMIND);
		if(textInput.find(MARKER_ENCLOSE, found+MARKER_REMIND_LENGTH)!=std::string::npos){
			foundComma = textInput.find(MARKER_COMMA, found+MARKER_REMIND_LENGTH);
			extractLength = determindExtractLength(found, foundComma, MARKER_REMIND, extractStartPos);
			i = foundComma;
			while(textInput[i]!=MARKER_ENCLOSE && i!=stringLength)
				marker += textInput[i++];
			if(marker==MARKER_AT || marker==MARKER_NEAR || marker==MARKER_REPEAT || marker==MARKER_BY || marker==MARKER_FROM || marker==MARKER_PRIORITY && textInput.find(MARKER_ON, found)!=std::string::npos){
				textRemindDateAndTime = _textInput.substr(extractStartPos, extractLength);
				shortenInput(found, foundComma);
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	else
		return true; 
}

bool Parser::determineSlot()
{
	int slotNumber =0;
	//istringstream iss(_textInput);
	string temp = _textInput;
	//iss >> temp;

	if(!isParseInt(temp, slotNumber))
		return false;
	textSlotNumber = std::to_string(slotNumber);
	
	return true;
}

bool Parser::determineTaskList()
{
	std::size_t found = 0;
	std::size_t stringLength = textInput.size();

	if(textInput.rfind(LIST_COMPLETED)!=std::string::npos){
		found = textInput.rfind(LIST_COMPLETED);
		textTaskList = _textInput.substr(found, LIST_COMPLETED_LENGTH);
		shortenInput(found, stringLength);
		return true;
	}
	else if(textInput.rfind(LIST_TO_DO)!=std::string::npos){
		found = textInput.rfind(LIST_TO_DO);
		textTaskList = _textInput.substr(found, LIST_TO_DO_LENGTH);
		shortenInput(found, stringLength);
		return true;
	}
	else if(textInput.rfind(LIST_OVERDUED)!=std::string::npos){
		found = textInput.rfind(LIST_OVERDUED);
		textTaskList = _textInput.substr(found, LIST_OVERDUED_LENGTH);
		shortenInput(found, stringLength);
		return true;
	}

	else
		return false;
}

std::size_t Parser::determindExtractLength(std::size_t found, std::size_t foundComma, string markConstant, std::size_t& extractStartPos)
{
	std::size_t extractEndPos;
	std::size_t shiftPos = INITIALIZE_SIZE_T;

	if(markConstant == MARKER_FROM || markConstant == MARKER_PRIORITY){
		shiftPos = shiftPos;
	}

	else
		shiftPos = markConstant.size();

	extractStartPos = found + (++shiftPos); //shift the pos to first pos of text to be extracted.
	extractEndPos = --foundComma;

	return extractEndPos - extractStartPos;
}

void Parser::shortenInput(std::size_t partitionStart, std::size_t partitionEnd)
{
	std::size_t partitionLength = partitionEnd-partitionStart;

	textInput.erase(partitionStart, partitionLength);
	_textInput.erase(partitionStart, partitionLength);
}



/*
int Parser::separateInput(int state)
{
string temp;
iss >> temp;

if(temp == ",at"){
temp.clear();
iss >> temp;
textVenue+= temp + " ";
return 1;
}
else if(temp ==",by"){
temp.clear();
iss >> temp;
textDateAndTime+= temp + " ";
return 2;
}
else if(state == 1){
textVenue+= temp + " ";
return 1;
}
else if (state == 2){
textDateAndTime+= temp + " ";
return 2;
}
else
{
textDescription += temp + " ";
}
}
*/

void Parser::populateContainer(vector<string>& inputBits)
{
	inputBits[SLOT_DESCRIPTION] = textDescription;
	inputBits[SLOT_LOCATION] = textVenue;
	inputBits[SLOT_REMIND_TIME] = textRemindDateAndTime;
	inputBits[SLOT_PRIORITY] = textPriority;
	inputBits[SLOT_REPEAT] = textRepeat;
	inputBits[SLOT_TIME] = textDateAndTime; 
	inputBits[SLOT_SLOT_NUMBER] = textSlotNumber;
	inputBits[SLOT_TASKLIST] = textTaskList;
}

void Parser::toLowerCase(string &str)
{
	const int length = str.length();
	for(int i=0; i < length; ++i)
	{
		str[i] = tolower(str[i]);
	}
}

//To retrieve the first word which is the command.
string Parser::getFirstWord(string input)
{
	string firstword;
	istringstream streamInput (input);
	streamInput >> firstword;
	return firstword;
}

//Remove the command from _input after retrieving it, change command to lower case
void Parser::removeFirstWord(string &input)
{
	textCommand = getFirstWord(input);
	std::size_t found = input.find(textCommand);
	toLowerCase(textCommand);
	input.replace(0, found+textCommand.length()+1, "");
}

//Check if the first character is a valid digit
bool Parser::isParseInt(string input, int &value)
{	
	if (isdigit(input[0]))
	{
		value = atoi(input.c_str());
		return 1;
	}
	else
		return 0;
}