SELECT name FROM people
WHERE id IN (
SELECT DISTINCT person_id FROM stars 
LEFT JOIN movies ON stars.movie_id = movies.id 
WHERE movies.year = 2004) 
ORDER BY people.birth;
