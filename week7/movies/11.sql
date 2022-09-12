SELECT title FROM movies LEFT JOIN ratings ON movies.id = ratings.movie_id 
LEFT JOIN stars ON movies.id = stars.movie_id LEFT JOIN people ON stars.person_id = people.id 
WHERE people.name == "Chadwick Boseman"
ORDER BY ratings.rating DESC LIMIT 5;