-- --------------------------------------------------------
-- Hôte :                        localhost
-- Version du serveur:           5.7.24 - MySQL Community Server (GPL)
-- SE du serveur:                Win64
-- HeidiSQL Version:             10.2.0.5599
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Listage des données de la table lifprojet_projets_ue_bdd.failed_jobs : ~0 rows (environ)
/*!40000 ALTER TABLE `failed_jobs` DISABLE KEYS */;
/*!40000 ALTER TABLE `failed_jobs` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.migrations : ~11 rows (environ)
/*!40000 ALTER TABLE `migrations` DISABLE KEYS */;
INSERT INTO `migrations` (`id`, `migration`, `batch`) VALUES
	(185, '2014_10_12_000000_create_users_table', 1),
	(186, '2014_10_12_100000_create_password_resets_table', 1),
	(187, '2019_08_19_000000_create_failed_jobs_table', 1),
	(188, '2020_04_06_084953_create_roles_table', 1),
	(189, '2020_04_06_090334_create_role_user_table', 1),
	(190, '2020_04_08_154529_create_foreign_keys_for_role_user_table', 1),
	(191, '2020_04_09_140500_create_ues_table', 1),
	(192, '2020_04_09_140906_create_ue_user_table', 1),
	(193, '2020_04_10_083842_create_projects_table', 1),
	(194, '2020_04_10_092359_create_ue_project_table', 1),
	(195, '2020_04_10_100436_create_project_ue_table', 1);
/*!40000 ALTER TABLE `migrations` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.password_resets : ~0 rows (environ)
/*!40000 ALTER TABLE `password_resets` DISABLE KEYS */;
/*!40000 ALTER TABLE `password_resets` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.projects : ~3 rows (environ)
/*!40000 ALTER TABLE `projects` DISABLE KEYS */;
INSERT INTO `projects` (`id`, `uuid`, `name`, `title`, `year`, `description`, `readme`, `mark`, `zip`, `git`, `images`, `created_at`, `updated_at`) VALUES
	(1, '786355b0-7e5f-11ea-a00a-b3d249cebc5f', 'Projet 1', 'Projet 1', 2018, 'Numquam amicitia ut ordinis quaedam esse tamquam parem Saepe Maximum.', NULL, 10.00, '', 'https://github.com/', '[]', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(2, '7863a020-7e5f-11ea-b198-5f2302eabfe2', 'Projet 2', 'Projet 2', 2019, 'Sunt qui etiam Sunt in opere putant putant ii contemni ut sunt se se modo.', NULL, 15.00, '', 'https://github.com/', '[]', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(3, '7863e540-7e5f-11ea-a3af-01d1c4af40cb', 'Projet 3', 'Projet 3', 2020, 'Caritas autem amicitiae ipsa adducta adducta ex ipsa quod hoc maxime.', NULL, 20.00, '', 'https://github.com/', '[]', '2020-04-14 14:51:49', '2020-04-14 14:51:49');
/*!40000 ALTER TABLE `projects` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.project_ue : ~3 rows (environ)
/*!40000 ALTER TABLE `project_ue` DISABLE KEYS */;
INSERT INTO `project_ue` (`id`, `project_id`, `ue_id`, `created_at`, `updated_at`) VALUES
	(1, 1, 1, NULL, NULL),
	(2, 2, 2, NULL, NULL),
	(3, 3, 3, NULL, NULL);
/*!40000 ALTER TABLE `project_ue` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.roles : ~3 rows (environ)
/*!40000 ALTER TABLE `roles` DISABLE KEYS */;
INSERT INTO `roles` (`id`, `name`, `created_at`, `updated_at`) VALUES
	(1, 'admin', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(2, 'author', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(3, 'user', '2020-04-14 14:51:49', '2020-04-14 14:51:49');
/*!40000 ALTER TABLE `roles` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.role_user : ~3 rows (environ)
/*!40000 ALTER TABLE `role_user` DISABLE KEYS */;
INSERT INTO `role_user` (`id`, `role_id`, `user_id`, `created_at`, `updated_at`) VALUES
	(1, 1, 1, NULL, NULL),
	(2, 2, 2, NULL, NULL),
	(3, 3, 3, NULL, NULL);
/*!40000 ALTER TABLE `role_user` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.ues : ~26 rows (environ)
/*!40000 ALTER TABLE `ues` DISABLE KEYS */;
INSERT INTO `ues` (`id`, `name`, `created_at`, `updated_at`) VALUES
	(1, 'LIFAP1', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(2, 'LIFASR1', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(3, 'LIFASR3', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(4, 'LIFAMI', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(5, 'LIFAP2', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(6, 'LIFASR2', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(7, 'LIFAP3', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(8, 'LIFBDW1', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(9, 'LIFASR4', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(10, 'LIFAP4', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(11, 'LIFAP5', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(12, 'LIFPROLOG', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(13, 'LIFGRAPHIQUE', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(14, 'LIFASR5', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(15, 'LIFIHM', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(16, 'LIFAP6', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(17, 'LIFASR6', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(18, 'LIFBDW2', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(19, 'LIFLC', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(20, 'LIFLF', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(21, 'LIFAP7', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(22, 'LIFPROJET', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(23, 'LIFASR7', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(24, 'LIFAlgoNum/Optim', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(25, 'LIFDATA', '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(26, 'LIFSTAGE', '2020-04-14 14:51:49', '2020-04-14 14:51:49');
/*!40000 ALTER TABLE `ues` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.ue_project : ~0 rows (environ)
/*!40000 ALTER TABLE `ue_project` DISABLE KEYS */;
/*!40000 ALTER TABLE `ue_project` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.ue_user : ~27 rows (environ)
/*!40000 ALTER TABLE `ue_user` DISABLE KEYS */;
INSERT INTO `ue_user` (`id`, `ue_id`, `user_id`, `created_at`, `updated_at`) VALUES
	(1, 1, 1, NULL, NULL),
	(2, 2, 1, NULL, NULL),
	(3, 3, 1, NULL, NULL),
	(4, 4, 1, NULL, NULL),
	(5, 5, 1, NULL, NULL),
	(6, 6, 1, NULL, NULL),
	(7, 7, 1, NULL, NULL),
	(8, 8, 1, NULL, NULL),
	(9, 9, 1, NULL, NULL),
	(10, 10, 1, NULL, NULL),
	(11, 11, 1, NULL, NULL),
	(12, 12, 1, NULL, NULL),
	(13, 13, 1, NULL, NULL),
	(14, 14, 1, NULL, NULL),
	(15, 15, 1, NULL, NULL),
	(16, 16, 1, NULL, NULL),
	(17, 17, 1, NULL, NULL),
	(18, 18, 1, NULL, NULL),
	(19, 19, 1, NULL, NULL),
	(20, 20, 1, NULL, NULL),
	(21, 21, 1, NULL, NULL),
	(22, 22, 1, NULL, NULL),
	(23, 23, 1, NULL, NULL),
	(24, 24, 1, NULL, NULL),
	(25, 25, 1, NULL, NULL),
	(26, 26, 1, NULL, NULL),
	(27, 2, 2, NULL, NULL);
/*!40000 ALTER TABLE `ue_user` ENABLE KEYS */;

-- Listage des données de la table lifprojet_projets_ue_bdd.users : ~3 rows (environ)
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` (`id`, `name`, `email`, `email_verified_at`, `password`, `remember_token`, `created_at`, `updated_at`) VALUES
	(1, 'Admin User', 'admin@admin.com', NULL, '$2y$10$QeTg0tMOk8ptz2LYJjKnX.snVlp15DRmvFtHmr6vJ9z4Jlr4ZoIjO', NULL, '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(2, 'Author User', 'author@author.com', NULL, '$2y$10$YOvvAyVaqv1v4CjDuYJV8.41rFFviMqiQU2QTxsj9sRic/omVlAOC', NULL, '2020-04-14 14:51:49', '2020-04-14 14:51:49'),
	(3, 'Generic User', 'user@user.com', NULL, '$2y$10$7WpKLmBXDREW9h0.nezimundriCx1tEPF5FnGX7SVHdYpildr4yGa', NULL, '2020-04-14 14:51:49', '2020-04-14 14:51:49');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
