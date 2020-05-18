#include "company.hpp"

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

// O(n)
CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  // delete all new companies
  for(int i=0;i<(int)newCompanies.size();++i){
    // delete if not null
    if(newCompanies[i]){
      delete newCompanies[i];
      newCompanies[i] = 0;
    }
  }
  // then delete base companies
  for(int i=0;i<numCompanies;++i){
    delete companies[i];
    companies[i] = 0;
  }
  // then delete companies pointer
  delete[] companies;
}

// O(n)
void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  // check if out of range
  if(!isValidCompany(i) || !isValidCompany(j)){
    return;
  }

  // check if in same company
  if(inSameCompany(i,j)){
    return;
  }

  // find largest company
  Company* m1 = findLargest(companies[i]);
  Company* m2 = findLargest(companies[j]);

  // create new company
  Company* newCompany = new Company(m1,m2);

  // update parent company for m1 & m2
  m1->parent = newCompany;
  m2->parent = newCompany;

  // add new company to vector
  newCompanies.push_back(newCompany);

  return;
}

// O(n)
void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  // check if valid
  if(!isValidCompany(i)){
    return;
  }

  // find largest
  Company* largest = findLargest(companies[i]);

  // check if base company, do nothing if base
  if(largest->merge1 == 0 && largest->merge2 == 0){
    return;
  }

  // set parent of m1 & m2 to null
  largest->merge1->parent = 0;
  largest->merge2->parent = 0;

  // find largest in vector
  int index;
  for(int i=0;i<(int)newCompanies.size();++i){
    if(newCompanies[i] == largest){
      index = i;
    }
  }

  // deallocate parent company
  delete largest;
  // update pointer in vector
  newCompanies[index] = 0;

  return;
}

// O(n)
bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  // check if they are valid inputs
  if(!isValidCompany(i) || !isValidCompany(j)){
    return false;
  }

  Company* c1 = findLargest(companies[i]);
  Company* c2 = findLargest(companies[j]);

  if(c1 == c2){
    return true;
  }
  else{
    return false;
  }

}

// finds the largest company
// O(n)
Company* CompanyTracker::findLargest(Company* company){
  Company* largest = company;
  // keep going until parent is null
  while(largest->parent){
    largest = largest->parent;
  }

  return largest;
}

// sees if company is valid
// O(1)
bool CompanyTracker::isValidCompany(int i){
  // if negative or greater or equal to numCompanies => invalid
  if(i < 0 || i >= numCompanies){
    return false;
  }
  else{
    return true;
  }
}