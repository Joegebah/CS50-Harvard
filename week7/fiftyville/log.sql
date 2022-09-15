--SELECT * FROM crime_scene_reports WHERE year == 2021 AND month == 7 AND day == 28 and street == "Humphrey Street"
-- !Theft took place at Humphrey Street at 10:15am, 3 interviewers!
--SELECT * FROM interviews WHERE year == 2021 AND month == 7 
--AND day == 28 AND name != "Jose" AND name != "Barbara" 
--AND name != "Lily" AND id != 159;
-- !Ruth, Eugene and Raymond -> within ten minutes of the theft, car, drove away
-- from bakery, ATM on Leggett Street, earlier this morning, withdrawing money,
-- thief called someone for less than a minute as they left the bakery,
-- planning to take earliest flight out of fiftyville -> Purchase flight ticket!
-- SELECT name FROM people LEFT JOIN bank_accounts ON people.id = bank_accounts.person_id
-- WHERE people.id IN(
-- SELECT person_id FROM bank_accounts LEFT JOIN atm_transactions
-- ON bank_accounts.account_number = atm_transactions.account_number
-- WHERE bank_accounts.account_number IN (
-- SELECT account_number FROM
-- atm_transactions WHERE atm_transactions.year == 2021 
-- AND atm_transactions.month == 7 AND atm_transactions.day == 28
-- AND atm_transactions.atm_location == "Leggett Street"));
-- SELECT * FROM atm_transactions WHERE atm_transactions.year == 2021 
-- AND atm_transactions.month == 7 AND atm_transactions.day == 28
-- AND atm_transactions.atm_location == "Leggett Street";
-- !all transactions done in that time frame: names -> Kenny, Iman, Benista, Taylor,
-- Brooke, Luca, Diana, Bruce, Kaelyn!
--SELECT * FROM airports
-- !determine the id of fiftyville airport, id == 8!
--SELECT * FROM flights WHERE origin_airport_id == 8 AND year == 2021 AND month == 7
--AND day == 29 ORDER BY hour, minute ASC;
-- !determine ealierst flight in the next day, id = 36, destination_id = 4
-- time frame hour = 8 minute = 20!
--SELECT name FROM people LEFT JOIN passengers ON people.passport_number = passengers.passport_number
--WHERE flight_id = 36
--SELECT name FROM people WHERE license_plate IN (
--SELECT license_plate FROM bakery_security_logs WHERE year == 2021 
--AND month == 7 AND day == 28 AND hour == 10 AND minute > 0 
--AND minute < 25 AND activity = "exit");
-- determine every person who had activity on exit in the bakery
-- in the given time frame in which the theft took place
-- next step -> Determine who of these people took a phone call in
-- given time frame
-- SELECT name FROM people LEFT JOIN phone_calls ON
-- people.phone_number = phone_calls.caller WHERE phone_number IN (
-- SELECT phone_number FROM people  WHERE name IN(
-- SELECT name FROM people WHERE license_plate IN (
-- SELECT license_plate FROM bakery_security_logs WHERE year == 2021 
-- AND month == 7 AND day == 28 AND hour == 10 AND minute > 0 
-- AND minute < 25 AND activity = "exit"))) AND duration < 60
-- AND year == 2021 AND month == 7 AND day == 28;
-- Now determine which one of them will be a passenger in next
-- day's flight:

SELECT name FROM people 
LEFT JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE people.id IN(
SELECT person_id FROM bank_accounts LEFT JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE bank_accounts.account_number IN (
SELECT account_number FROM
atm_transactions WHERE atm_transactions.year == 2021 
AND atm_transactions.month == 7 AND atm_transactions.day == 28
AND atm_transactions.atm_location == "Leggett Street"));

SELECT name FROM people 
LEFT JOIN passengers ON people.passport_number = passengers.passport_number
WHERE name IN (
SELECT DISTINCT name FROM people LEFT JOIN phone_calls ON
people.phone_number = phone_calls.caller WHERE phone_number IN (
SELECT phone_number FROM people  WHERE name IN(
SELECT name FROM people WHERE license_plate IN (
SELECT license_plate FROM bakery_security_logs WHERE year == 2021 
AND month == 7 AND day == 28 AND hour == 10 AND minute > 0 
AND minute < 25 AND activity = "exit"))) AND duration < 60
AND year == 2021 AND month == 7 AND day == 28) AND flight_id = 36;

--From the ouputs we can learn who took transactions at given time in
--Leggett Street (early morning where the theft took place) and 
--which people took a phone call when leaving the bakery after the theft
--took place AND drove away with the car with the given license_plate

--After examining both tables, there is one name which appears in both
--tables, Bruce. Bruce must be the thief of the CS50 duck. Now the
--accomplice...
SELECT name FROM people
LEFT JOIN phone_calls ON people.phone_number = phone_calls.receiver 
WHERE caller IN (
SELECT phone_number FROM people WHERE name == "Bruce") AND year == 2021
AND month == 7 AND day == 28 AND duration < 60;
