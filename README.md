<h3>Movie Rental App</h3>
<strong>October 2014 to November 2014</strong>
<br><br>
<strong>About:</strong><br>
This application simulates the backend of a popular movie streaming and rental platform using data structures such as Map and Set. It include features such as search by title, actor, or subject; a movie check-out and check-in system; a movie rating system; a user login and registration system; persistant data tracking; and a movie recommendation system based on user's previous movie ratings. The frontend was developed using the Qt library. The backend originally utilized my own data structures, but was later replaced with STL classes for extra credit.
<br><br>
<strong>Quick Start Guide:</strong><br>
1. Enter qt-workspace directory by typing <code>cd qt-workspace</code>.<br>
2. Type the following, in order, to make: <code>qmake -project</code> <code>qmake</code> <code>make</code>.<br>
3. Run the program by entering <code>./qt-workspace data.txt</code>.<br>
<hr />

<h3>Project Part 4 (Final)</h3>

<ol>
<li>Enter qt-workspace directory by typing <code>cd qt-workspace</code>.</li>
<li>Type the following, in order, to make: <code>qmake -project</code> <code>qmake</code> <code>make</code>.</li>
<li>Run the program by entering <code>./qt-workspace data.txt</code>.</li>
</ol>

<ul>
<li> <strong>Note:</strong> Do not log in with the same username if you have just logged out. This will delete the user's queue. </li>
<li> <strong>Note:</strong> Quit the program entirely after successfully creating a new user. Not doing so may end up crashing the program. </li>
<li> <strong>Note:</strong> Feel free to use the provided 'refresh' button if the window doesn't update. </li>
<li><strong>Note:</strong> Formats for data files have been changed. See the samples given in <code>qt-workspace/data</code>.</li>
<li><strong>Note:</strong> Do NOT use the data files in <code>data/</code> as they are for non-QT parts of the project.</li>
<li><strong>Note:</strong> The Dijkstra's part (10%) of the similarity estimate was not implemented. The basic similarity factor is the one used in recommending.</li>
</ul>

I attempted the following options (6 bells & whistles):
- STL Data Structures
- Actors
- User Fields
- Modify Ratings



<em>Last modified December 7th</em>



<hr />

<h3>Project Part 1</h3>
<ul>
<li>To open the application, while in the uppermost directory, type <code>make all</code> then <code>./bin/movie_app data.txt</code></li>
<li>Note that all data files must exist in the 'data' subdirectory.</li>
<li>'bin' will be automatically generated when 'make all' is ran.</li>
</ul>

<em>Last modified October 12th</em>

<hr />

<h3>Project Part 2</h3>
<ul>
<li>To open the application, while in the uppermost directory, type <code>make all</code> then <code>./bin/movie_app data.txt</code></li>
<li>Note that all data files must exist in the 'data' subdirectory.</li>
<li>'bin' will be automatically generated when 'make all' is ran.</li>
<li> The gtest <code>set_test.cpp</code> can be accessed in the tests folder.</li>
<li> <strong>Note:</strong> Log out alone will not save the user's current queue. User must exit the program all the way for the queue to be saved onto the user database. </li>
<li> <strong>Note:</strong> The only way to add a movie to queue is to search a movie by keyword, and only by a keyword. </li>
</ul>

<em>Last modified October 29th</em>

<hr />

<h3>Project Part 3</h3>

<ol>
<li>Enter qt-workspace directory by typing <code>cd qt-workspace</code>.</li>
<li>Type the following, in order, to make: <code>qmake -project</code> <code>qmake</code> <code>make</code>.</li>
<li>Run the program by entering <code>./qt-workspace data.txt</code>.</li>
</ol>

<ul>
<li> <strong>Note:</strong> DO NOT log in with the same username if you have just logged out. This will delete the user's queue. </li>
<li> <strong>Note:</strong> You may need to click the 'refresh' button (only) after adding movie to queue. Every other function will automatically refresh the window. </li>
<li> <strong>Note:</strong> Searching for a movie by keyword may display multiple movie information simutaneously. </li>
<li> <strong>Note:</strong> This program CANNOT track the "Movie" keyword in its user data file. Having this keyword in its data file will result in errors.
</ul>

<em>Last modified November 30th</em>

