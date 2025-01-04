KEY = "7d89c730c4a150b1973d2bcb7122e3f7"
URL = "https://api.themoviedb.org/3"

import requests
import os

def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

def get_movie():
    clear()
    while True:    
        user_input = input("Movie: ")

        endpoint = f"{URL}/search/movie"
        params = {
            "api_key": KEY,
            "query": user_input,
            "language": "en-US",
            "page": 1,
            "include_adult": False
        }
        
        response = requests.get(endpoint, params=params)

        data = response.json()

        if not data.get('results'):
            continue
            
        while True:
            print(f"{data['results'][0]['original_title']} released {data['results'][0]['release_date']}")

            user_input = input("Select a command\n1. Correct movie\n2. Select a different movie\n3. Exit\n")

            if user_input == '1':
                return data['results'][0]
            elif user_input == '2':
                break
            elif user_input == '3':
                return None

def add_watched(movie, movies):
    movies['watched'][movie[0]] = movie

    clear()
    while True:
        try:
            rating = float(input('Rate the movie fromm 1 to 10: '))
        except ValueError:
            pass

        if rating >= 1 and rating <= 10:
            break

    movies['watched'][movie[0]].append(rating)

def select_from_list(my_list):
    clear()
    if not my_list:
        return None
    print('Select a movie: ')

    i = 1
    for movie in my_list:
        print(f"{i}. {movie}")
        i += 1

    user_input = input()

    if user_input.isdigit() and int(user_input) <= len(my_list) and int(user_input) > 0:
        return my_list[int(user_input) - 1]

def watchlist(movies):
    while True:
        clear()
        user_input = (input("Select a command\n1. View lists\n2. Add planned movie\n3. Move to watched\n4. Remove planned movie\n5. Add watched movie\n6. Remove watched movie\n7. Exit\n"))

        if user_input == '1':
            clear()
            print("Watched movies: ")
            i = 1
            for movie in movies['watched']:
                print(f"{i}. {movies['watched'][movie][0]} {movies['watched'][movie][2]}/10")
                i += 1
            
            print("\nPlanned movies: ")
            i = 1
            for movie in movies['planned']:
                print(f"{i}. {movies['planned'][movie][0]}")
                i += 1
            
            input("\nEnter to continue")
        elif user_input == '2':
            movie = get_movie()

            if movie and not movies['planned'].get(movie['original_title']):
                movies['planned'][movie['original_title']] = [movie['original_title'], movie['genre_ids']]
        elif user_input == '3':
            movie = select_from_list(list(movies['planned'].keys()))

            if movie:
                add_watched(movies['planned'][movie], movies)
                del movies['planned'][movie]
        elif user_input == '4':
            movie = select_from_list(list(movies['planned'].keys()))
            if movie:
                del movies['planned'][movie]
        elif user_input == '5':
            movie = get_movie()
            add_watched([movie['original_title'], movie['genre_ids']], movies)
        elif user_input == '6':
            movie = select_from_list(list(movies['watched'].keys()))
            if movie:
                del movies['watched'][movie]
        elif user_input == '7':
            break

def get_movies(genre_id=None, page=1):
    url = f"{URL}/discover/movie"
    params = {
        "api_key": KEY,
        "language": "en-US",
        "sort_by": "vote_count.desc",
        "page": page
    }
    
    if genre_id:
            params["with_genres"] = genre_id

    response = requests.get(url, params=params)
    if response.status_code == 200:
        data = response.json()
        return data.get("results", [])
    else:
        print(f"Error: {response.status_code}, {response.text}")
        return []

def print_movies(movies, suggestions, genres, user_movie=None):
    clear()
    if genres:    
        print(f"Popular movies in {' and '.join(genres)}")
    else:
        print("Popular movies")

    if user_movie:
        user_movie = user_movie['original_title']
            
    i = 0
    for movie in suggestions:
        if movie['original_title'] not in movies['watched'] and movie['original_title'] != user_movie:
            i += 1
            print(movie['original_title'])
        
        if i == 5:
            break
    
    input()

def suggest(movies):
    endpoint = f"{URL}/genre/movie/list"
    params = {
        "api_key": KEY,
        "language": "en-US"
    }

    response = requests.get(endpoint, params=params)
    data = response.json()
    
    genres = {genre['id']: genre['name'] for genre in data.get('genres', [])}
    
    while True:
        # clear the comman line
        clear()

        user_input = (input("Select a command\n1. Suggestion from watchlist\n2. Suggestion from specific movie\n3. Suggestion by genre\n4. Popular suggestions\n5. Exit\n"))

        if user_input == '1':
            print("hi")
        elif user_input == '2':
            user_movie = get_movie()
            user_genres = user_movie['genre_ids']

            suggestions = get_movies(user_genres)

            genre_names = [genres.get(genre, "Unknown") for genre in user_genres]

            print_movies(movies, suggestions, genre_names, user_movie)
        elif user_input == '3':
            user_genre = select_from_list(list(genres.values()))

            if user_genre:
                for id in genres:
                    if genres[id] == user_genre:
                        user_id = [id]
                        break

                suggestions = get_movies(user_id)

                print_movies(movies, suggestions, [user_genre])
        elif user_input == '4':
            suggestions = get_movies()

            print_movies(movies, suggestions, None)
        elif user_input == '5':
            clear()
            break

def main():
    movies = {'watched' : {}, 'planned' : {}}
    while True:
        # clear the comman line
        clear()

        user_input = (input("Select a command\n1. Review watchlist\n2. Generate suggestions\n3. Exit\n"))

        if user_input == '1':
            watchlist(movies)
        elif user_input == '2':
            suggest(movies)
        elif user_input == '3':
            clear()
            break

if __name__ == "__main__":
    main()
