//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<fstream>
#include	<iostream>
#include	<string>
#include	<map>

#include	"Catalog.h"

using namespace std;

bool	Catalog::AddCategory(uint64_t categoryNumber, const string& name)
{
	// Check if the category number already exists. Return false if it already exists.
	// Otherwise, add the category to the catalog and return true.
	if (category.find(categoryNumber) != category.end())
	{
		return false;
	}
	else
	{
		categoryClass newCategory(name);	// declare new object newCategory
		category.insert(std::pair<int, categoryClass>(categoryNumber, newCategory));	// insert the category
		numCategory++;
	}
	return true;
}

bool	Catalog::AddProduct(uint64_t categoryNumber, uint64_t productNumber, const string& name)
{
	// Add the product with a category number, product number, and product name to catalog.
	// Return false if category number doesn't exist in catalog or if the product number
	// already exists within the category.
	std::map<int, categoryClass>::iterator it;

	it = category.find(categoryNumber);

	if (it != category.end())
	{
		std::map<int, string>::iterator itProduct;
		itProduct = (it->second).product.find(productNumber);

		if (itProduct != (it->second).product.end())
		{
			return false;
		}
		else
		{
			(it->second).product.insert(std::pair<int, string>(productNumber, name));	// insert the product
			(it->second).numProduct++;
		}
	}
	else
	{
		return false;
	}

	return true;
}

uint64_t	Catalog::GetCategoryCount()
{
	// Return the number of categories.
	return numCategory;
}

int64_t	Catalog::GetProductCount(uint64_t categoryNumber)
{
	// Return the number of products only if the category exists.
	// Otherwise, return a -1.

	std::map<int, categoryClass>::iterator it;

	it = category.find(categoryNumber);

	if (it == category.end())
	{
		return -1;
	}
	else
	{
		return (it->second).numProduct;
	}
}

bool	Catalog::Load(const string& fileName)
{
	// Load the catalog from the file. Return false if the file
	// can't be loaded (it doesn't exist or it is in incorrect format).
	ifstream myfile(fileName);
	string line;
	if (!myfile.is_open())
	{
		return false;
	}
	else
	{
		uint64_t categoryNumber;
		while (!myfile.eof())	// While file is not end of file...
		{
			getline(myfile, line);	// Needed to compare strings in file
			int npos1, npos2;	// Needed to locate the substrings

			npos1 = line.find('\t');
			string firstWord = line.substr(0, npos1);
			if (firstWord == "Category")
			{
				npos2 = line.find('\t', npos1 + 1);
				string secondWord = line.substr(npos1 + 1, npos2 - npos1 - 1);
				string thirdWord = line.substr(npos2 + 1, string::npos);

				categoryNumber = stoi(secondWord);
				AddCategory(categoryNumber, thirdWord);
			}
			else if (!firstWord.empty())
			{
				string secondWord = line.substr(npos1 + 1, string::npos);	// secondWord is product name
				uint64_t productNumber = stoi(firstWord);

				AddProduct(categoryNumber, productNumber, secondWord);
			}
		}
		myfile.close();	// Close the file when done
	}
	return true;
}

//****************************************************************************************
//
//	Show... methods
//
//	The stream argument allows these functions to write its output to any output stream,
//	such as cout or a file, that the caller passes. The argument's name "stream" should
//	be used just as you would use "cout":
//
//		stream << "X = " << x << endl;
//
//	The output will go where the caller intended without special action by this function.
//
//****************************************************************************************

bool	Catalog::ShowProduct(ostream& stream, uint64_t categoryNumber, uint64_t productNumber)
{
	// Display product number and name seperated by tab given by category number and product number.
	// Return false only if either the category number or the product number doesn't exist in the catalog.
	std::map<int, categoryClass>::iterator it;

	it = category.find(categoryNumber);

	if (it != category.end())
	{
		std::map<int, string>::iterator itProduct;
		itProduct = (it->second).product.find(productNumber);

		// Check if the product exists.
		if (itProduct != (it->second).product.end())
		{
			// Display the product number and product name seperated by tab
			stream << productNumber << '\t' << itProduct->second;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool	Catalog::ShowCategory(ostream& stream, uint64_t categoryNumber)
{
	// Display products in order by product number given by category number.
	// Return false if the category number doesn't exist in the catalog.

	std::map<int, categoryClass>::iterator it;

	it = category.find(categoryNumber);

	if (it == category.end())
	{
		return false;
	}
	else
	{	// First, display Category followed by the category number and category name.
		// Then, use the for loop to print out the product number and product name.
		stream << "Category\t" << categoryNumber << '\t' << it->second.categoryName << endl;
		std::map<int, string>::iterator itProduct;
		for (itProduct = it->second.product.begin(); itProduct != it->second.product.end(); itProduct++)
		{
			stream << itProduct->first << '\t' << itProduct->second << endl;
		}
	}
	return true;
}

bool	Catalog::ShowAll(ostream& stream)
{
	// Display the entire catalog category by category in order by category number.
	// For each category, display all products in order by product number.
	// Return false if the file cannot be loaded.
	std::map<int, categoryClass>::iterator it;
	// Check if the category is empty.
	if (category.empty())
	{
		return false;
	}
	else
	{
		// Inside the for loop, call the ShowCategory via recursion.
		for (it = category.begin(); it != category.end(); it++)
		{
			ShowCategory(stream, it->first);
		}
	}
	return true;
}