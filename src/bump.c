/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoricon <lmoricon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:41:29 by lmoricon          #+#    #+#             */
/*   Updated: 2025/04/23 18:46:28 by lmoricon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * bump - Perturbs the normal vector of the hit by a random amount.
 * @hit: Pointer to the hit structure to modify the normal vector.
 *
 * This function perturbs the normal vector in each direction by a random
 * amount scaled by the ROUGHNESS parameter. The perturbation is clamped
 * to ensure the resulting vector remains normalized.
 */
void	bump(t_hit *hit)
{
	t_vec	perturbation;

	perturbation.x = ((float)rand()
			/ (float)RAND_MAX - 0.5f) * 2.0f * ROUGHNESS;
	perturbation.y = ((float)rand()
			/ (float)RAND_MAX - 0.5f) * 2.0f * ROUGHNESS;
	perturbation.z = ((float)rand()
			/ (float)RAND_MAX - 0.5f) * 2.0f * ROUGHNESS;
	hit->normal = vecsum(hit->normal, perturbation);
	hit->normal = normalize(hit->normal);
}
