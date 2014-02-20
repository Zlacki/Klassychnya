/**
 *
 * SLACKNET CONFIDENTIAL
 * __________________
 *
 *  [2012] - [2013] SlackNet, LLC
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of SlackNet, LLC and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to SlackNet, LLC
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from SlackNet, LLC.
 */

#include "util.h"

void *safe_malloc(size_t size) {
	void *ptr = malloc(size);
	if(ptr == NULL ) {
		puts("SEVERE: Could not allocate enough memory.");
		exit(1);
	}

	return ptr;
}
