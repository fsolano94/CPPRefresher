#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

class User
{
protected:
	int id;
	std::string emailAddress;
	enum Role
	{
		Admin,
		Standard
	} role;

public:
	// pure virtual function
	void UpdateEmailAddress(std::string newEmailAddress)
	{
		emailAddress = newEmailAddress;
	}
	void LogUsersRoleToConsole()
	{
		std::cout << "role = " << getRoleAsString() << std::endl;
	}
	void LogUsersEmailToConsole()
	{
		std::cout << "email = " << emailAddress << std::endl;
	}
	void LogUsersIdToConsole()
	{
		std::cout << "id = " << id << std::endl;
	}
	std::string getUserEmail() { return emailAddress; }
	int getUserId() { return id; }
	std::string getRoleAsString()
	{
		switch (role)
		{
		case Admin: return "Administrator";

		case Standard: return "Standard User";

		default: return "Undefined";
		}
	}

};

class Administrator : public User
{
public:
	Administrator(int userId, std::string emailAddr)
	{
		role = Admin;
		emailAddress = emailAddr;
		id = userId;
	}
};


class StandardUser : public User
{
public:
	StandardUser(int userId, std::string emailAddr)
	{
		role = Standard;
		emailAddress = emailAddr;
		id = userId;
	}
};

class UserRepository
{
public:
	UserRepository(std::vector<std::shared_ptr<User>> users)
	{
		_users = users;
	}
	bool SaveUsersToFile(std::string filePathAndName)
	{
		std::ofstream outputFileStream(filePathAndName);

		if (_users.size() > 0)
		{
			for (int index = 0; index < _users.size(); index++)
			{
				outputFileStream << std::endl;
				outputFileStream << "id = " << _users[index]->getUserId() << std::endl;
				outputFileStream << "role = " << _users[index]->getRoleAsString() << std::endl;
				outputFileStream << "email = " << _users[index]->getUserEmail() << std::endl;
				outputFileStream << std::endl;
			}
			return true;
		}
		return false;
	}
private:
	std::vector<std::shared_ptr<User>> _users;
};

void CreateUsersAndDisplayTheirRoles_1();
void CreateUsersAndDisplayTheirRoles_2();

void CreateUsersAndSaveThemToAFile();

int main(int argc, char* const argv[])
{
	std::cout << "Entering main." << std::endl;

	CreateUsersAndSaveThemToAFile();

	std::cout << "Exiting main." << std::endl;
	std::cin.get();
	return 0;
}

void CreateUsersAndDisplayTheirRoles_1()
{
	std::vector< User* > users;

	Administrator* newAdministrator = new Administrator(1, "admin1@gmail.com");

	StandardUser* newStandardUser = new StandardUser(2, "standarduser1@gmail.com");

	users.push_back(newAdministrator);

	users.push_back(newStandardUser);

	for (int index = 0; index < users.size(); index++)
	{
		users[index]->LogUsersIdToConsole();
		users[index]->LogUsersRoleToConsole();
		users[index]->LogUsersEmailToConsole();
	}
}

void CreateUsersAndDisplayTheirRoles_2()
{
	std::vector< std::shared_ptr<User> > users = 
	{
		std::make_shared<Administrator>(1, "admin1@gmail.com"),
		std::make_shared<StandardUser>(2, "standarduser1@gmail.com")
	};

	for(std::shared_ptr<User> user : users)
	{
		user->LogUsersIdToConsole();
		user->LogUsersRoleToConsole();
		user->LogUsersEmailToConsole();
	}
}

void CreateUsersAndSaveThemToAFile()
{
	std::cout << "Creating Users..." << std::endl;

	std::vector< std::shared_ptr<User> > users =
	{
		std::make_shared<Administrator>(1, "admin1@gmail.com"),
		std::make_shared<StandardUser>(2, "standarduser1@gmail.com")
	};
	
	std::cout << "Created users successfully." << std::endl;

	UserRepository* userRepository = new UserRepository(users);
	std::string filePathAndName;

	std::cout << "Enter the full file path and file name where the users will be saved: ";
	std::getline(std::cin, filePathAndName);

	std::cout << "Now saving users to " << filePathAndName << std::endl;

	userRepository->SaveUsersToFile(filePathAndName);

	std::cout << "Successfully saved users to " << filePathAndName << std::endl;

}

