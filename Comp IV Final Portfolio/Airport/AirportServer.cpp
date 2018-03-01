#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "AirportServer.h"


/**
*  Called by an Airplane when it wishes to land on a runway
*/


// array to keep track of which runways are currently locked. false = unlocked, true = locked.
// order is			4L,		4R,		9,    14,   15L, 15R
bool isLocked[] = { false, false, false, false, false, false };

void AirportServer::reserveRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	bool TO_MANY_LANDING_REQUESTS = false;
	// Acquire runway(s)
	{  // Begin critical region

		unique_lock<mutex> runwaysLock(runwaysMutex);
	
		{
			lock_guard<mutex> lk(AirportRunways::checkMutex);
		
			cout << "Airplane #" << airplaneNum << " is acquiring any needed runway(s) for landing on Runway "
				 << AirportRunways::runwayName(runway) << endl;
		}

		/**
		 *  ***** Add your synchronization here! *****
		 */
		 // for now just get plane to only land if all runways are empty
		 // for the realthing maybe write a bool func. that uses a switch statement
		 // to check the real conditions for landing. and return Bool_function() 
		 // instead of (runways_in_use < 2)
		runwayCV.wait(runwaysLock, [&] {
			bool ok = false;

			// switch statement checks for conflicts between runways
			switch (runway) {
			case 0:
				if (!isLocked[0] && !isLocked[4] && !isLocked[5]) {
					isLocked[0] = true;
					isLocked[4] = true;
					isLocked[5] = true;
					ok = true; // if all three runways have been locked by the thread landing can start
				}
				// this thread should now have locked the runways (mutexes) 4L, 15L, and 15R
				break;
			case 1:
				if (!isLocked[1] && !isLocked[2] && !isLocked[4] && !isLocked[5]) {
					isLocked[1] = true; //4R
					isLocked[2] = true; //9
					isLocked[4] = true; //15L
					isLocked[5] = true; //15R
					ok = true; // if all four runways have been locked by the thread landing can start
								// this thread should now have locked the runways (booleans) 4R, 9, 15L, and 15R	
				}
				break;
			case 2:
				if (!isLocked[1] && !isLocked[2] && !isLocked[5]) {
					isLocked[1] = true; // 4R
					isLocked[2] = true; // 9
					isLocked[5] = true; // 15R
					ok = true; // if all three runways have been locked by the thread landing can start
				}
				// this thread should now have locked the runways (mutexes) 4R, 9, and 15R
				break;
			case 3:
				if (!isLocked[3]) {

					isLocked[3] = true; // 14
					ok = true; // if the runway has been locked by the thread landing can start
				}
				// this thread should now have locked the runway 14
				break;
			case 4:
				if (!isLocked[0] && !isLocked[1] && !isLocked[4]) {
					isLocked[0] = true; // 4L
					isLocked[1] = true; // 4R
					isLocked[4] = true; // 15L
					ok = true; // if all three runways have been locked by the thread landing can start
				}
				// this thread should now have locked the runways 4L, 4R, and 15L
				break;
			case 5:
				if (!isLocked[0] && !isLocked[1] && !isLocked[2] && !isLocked[5]) {
					isLocked[0] = true; // 4L
					isLocked[1] = true; // 4R
					isLocked[2] = true; //9
					isLocked[5] = true; // 15R
					ok = true; // if all four runways have been locked by the thread landing can start
				}
				// this thread should now have locked the runways 4L, 4R, and 15L
				break;
			default: ok = false; std::cout << "Something bad happened in reserveRunway." << endl; break;
			}
			// check that total current landing requests are below the maximum number allowed
			// because we need an empty "slot" for this one.
			if (AirportRunways::getNumLandingRequests() >= AirportRunways::MAX_LANDING_REQUESTS) {
				ok = true;
				TO_MANY_LANDING_REQUESTS = true; // This will eventually be flag to make the plane skip back to waiting
			}
			return ok;});
		//if (TO_MANY_LANDING_REQUESTS) {// finish fixing this later
			//std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

//		}

		// update runways_in_use counter
		AirportRunways::incNumLandingRequests();		

		/*End add synchronization section*/

		// Check status of the airport for any rule violations
		AirportRunways::checkAirportStatus(runway);

		runwaysLock.unlock();
	} // End critical region

	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Taxi for a random number of milliseconds
	std::uniform_int_distribution<int> taxiTimeDistribution(1, MAX_TAXI_TIME);
	int taxiTime = taxiTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is taxiing on Runway " << AirportRunways::runwayName(runway)
			 << " for " << taxiTime << " milliseconds\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(taxiTime));

} // end AirportServer::reserveRunway()


 /**
  *  Called by an Airplane when it is finished landing
  */
void AirportServer::releaseRunway(int airplaneNum, AirportRunways::RunwayNumber runway)
{
	// Release the landing runway and any other needed runways
	{ // Begin critical region

		unique_lock<mutex> runwaysLock(runwaysMutex);
		
		{
			lock_guard<mutex> lk(AirportRunways::checkMutex);

			cout << "Airplane #" << airplaneNum << " is releasing any needed runway(s) after landing on Runway "
				 << AirportRunways::runwayName(runway) << endl;
		}
		/**
		*  ***** Add your synchronization here! *****
		*/
		switch (runway) {
		case 0:
				isLocked[0] = false;
				isLocked[4] = false;
				isLocked[5] = false;
			break;
		case 1:
				isLocked[1] = false; //4R
				isLocked[2] = false; //9
				isLocked[4] = false; //15L
				isLocked[5] = false; //15R
			break;
		case 2:
				isLocked[1] = false; // 4R
				isLocked[2] = false; // 9
				isLocked[5] = false; // 15R
			break;
		case 3:
			
				isLocked[3] = false; // 14
			break;
		case 4:
				isLocked[0] = false; // 4L
				isLocked[1] = false; // 4R
				isLocked[4] = false; // 15L
			break;
		case 5:
				isLocked[0] = false; // 4L
				isLocked[1] = false; // 4R
				isLocked[2] = false; //9
				isLocked[5] = false; // 15R
			break;
		default: std::cout << "Something bad happened in reserveRunway." << endl; break;
		}

		// update runways_in_use counter
		AirportRunways::decNumLandingRequests();
		

		runwayCV.notify_all();
		//end add synchronization*****************************************

		// Update the status of the airport to indicate that the landing is complete
		AirportRunways::finishedWithRunway(runway);

		runwaysLock.unlock();

	} // End critical region

	// obtain a seed from the system clock:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	// Wait for a random number of milliseconds before requesting the next landing for this Airplane
	std::uniform_int_distribution<int> waitTimeDistribution(1, MAX_WAIT_TIME);
	int waitTime = waitTimeDistribution(generator);

	{
		lock_guard<mutex> lk(AirportRunways::checkMutex);

		cout << "Airplane #" << airplaneNum << " is waiting for " << waitTime << " milliseconds before landing again\n";
	
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

} // end AirportServer::releaseRunway()

