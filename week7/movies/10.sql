SELECT name FROM people 
WHERE id IN (
SELECT DISTINCT directors.person_id FROM directors
LEFT JOIN ratings ON directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0)
