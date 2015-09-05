-- add a public and non-public user for testing.
INSERT INTO users (id, email, pass_crypt, creation_time, display_name, data_public)
-- note the user with ID -1 is equivalent to one that osmosis would add when
-- writing an apidb from a planet file or extract.
VALUES (-1, 'osmosis@osmosis.com', '', '2016-04-16T15:09:00Z', 'osmosis', false),
       (1, 'user_1@example.com', '', '2013-11-14T02:10:00Z', 'user_1', true),
       (2, 'user_2@example.com', '', '2013-11-14T02:10:00Z', 'user_2', false);

-- give the users some changesets
INSERT INTO changesets (id, user_id, created_at, closed_at)
-- note the changesets with IDs -1 and 0 are equivalent to ones that osmosis
-- creates when reading PBF files?
VALUES (-1, -1, '2016-04-16T15:09:00Z', '2016-04-16T15:09:00Z'),
       (0, -1, '2016-04-16T15:09:00Z', '2016-04-16T15:09:00Z'),
       (1, 1, '2013-11-14T02:10:00Z', '2013-11-14T03:10:00Z'),
       (2, 1, '2013-11-14T02:10:00Z', '2013-11-14T03:10:00Z'),
       (3, 1, '2013-11-14T02:10:00Z', '2013-11-14T03:10:00Z'),
       (4, 2, '2013-11-14T02:10:00Z', '2013-11-14T03:10:00Z');

-- add some nodes for each of the users
INSERT INTO current_nodes (id, latitude, longitude, changeset_id, visible, "timestamp", tile, version)
VALUES (1,       0,       0, 1, true,  '2013-11-14T02:10:00Z', 3221225472, 1),
       (2, 1000000, 1000000, 1, true,  '2013-11-14T02:10:01Z', 3221227032, 1),
       (3,       0,       0, 2, false, '2015-03-02T18:27:00Z', 3221225472, 2),
       (4,       0,       0, 4, true,  '2015-03-02T19:25:00Z', 3221225472, 1),
       -- note: node 5 intentionally missing
       (6, 90000000, 90000000,  0, true,  '2016-04-16T15:09:00Z', 3229120632, 1),
       (7, 90000000, 90000000, -1, true,  '2016-04-16T15:09:00Z', 3229120632, 1);

-- add some OAuth tokens, one valid and the others revoked or not valid.
-- the API is publicly readable, so _all_ tokens can read the API. there is no
-- "allow_read_api" setting on the token itself. but some tokens might have been
-- revoked or expired.
INSERT INTO oauth_tokens
  (id, user_id, token, secret, created_at, authorized_at, invalidated_at)
VALUES
  -- valid key
  (1, 1,
   'OfkxM4sSeyXjzgDTIOaJxcutsnqBoalr842NHOrA',
   'fFCKdXsLxeHPlgrIPr5fZSpXKnDuLw0GvJTzeE99',
   '2016-07-11T19:12:00Z', '2016-07-11T19:12:00Z', NULL),
  -- not authorized
  (2, 1,
   'wpNsXPhrgWl4ELPjPbhfwjjSbNk9npsKoNrMGFlC',
   'NZskvUUYlOuCsPKuMbSTz5eMpVJVI3LsyW11Z2Uq',
   '2016-07-11T19:12:00Z', NULL, NULL),
  -- invalidated
  (3, 1,
   'Rzcm5aDiDgqgub8j96MfDaYyAc4cRwI9CmZB7HBf',
   '2UxsEFziZGv64hdWN3Qa90Vb6v1aovVxaTTQIn1D',
   '2016-07-11T19:12:00Z', '2016-07-11T19:12:00Z', '2016-07-11T19:12:00Z');

-- update the number of edits
UPDATE changesets
  SET num_changes = (
    SELECT count(*)
    FROM current_nodes
    WHERE changeset_id = changesets.id);
