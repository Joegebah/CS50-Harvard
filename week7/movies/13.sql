SELECT name FROM people WHERE name != "Kevin Bacon" AND id IN (
SELECT person_id FROM stars WHERE movie_id IN (
SELECT movie_id FROM stars LEFT JOIN people ON stars.person_id = people.id 
WHERE people.name == "Kevin Bacon" AND people.birth == 1958));