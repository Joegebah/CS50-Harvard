SELECT AVG(energy) 
FROM songs 
INNER JOIN artists ON artist_id = artists.id 
WHERE artists.name = "Drake";
