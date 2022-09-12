--SELECT * FROM crime_scene_reports WHERE year == 2021 AND month == 7 AND day == 28;
--Theft took place at Humphrey Street bakery at 10:15am
SELECT * FROM interviews WHERE year == 2021 AND month == 7 AND day == 28
AND id != 159 AND id != 160 AND id != 158 AND id != 191;

--earliest flight tomorror out of Fiftyville
--SELECT * FROM airports;
--SELECT passport_number FROM passengers WHERE flight_id IN (
--SELECT * FROM flights WHERE origin_airport_id == 8 AND day == 29 ORDER BY hour, minute ASC;
--earliest flight ID 36, 8:20AM
--SELECT name FROM people WHERE passport_number IN(
--SELECT passport_number FROM passengers LEFT JOIN flights ON passengers.flight_id = flights.id 
--WHERE origin_airport_id == 8 AND day == 29 AND hour == 8 AND minute == 20);
